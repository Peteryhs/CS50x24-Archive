import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    data = db.execute("SELECT stock, amount FROM brought WHERE username IS ?;  ",
                      session["user_id"])

    return render_template("index.html", data=data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        shares = request.form.get("shares")
        stock = request.form.get("symbol")
        data = lookup(stock)
        if not shares.isdigit() or int(shares) <= 0:
            return apology("Shares must be a positive whole number")

        shares = int(shares)

        print(session["user_id"])
        money = int([row['cash'] for row in db.execute(
            "SELECT cash FROM users WHERE id IS ?; ", session["user_id"])][0])
        print(money)
        if isinstance(data, dict):
            price = data['price']
            if money < (price * shares):
                return apology("U R 2 Poor")
            else:
                money_used = money - (price * shares)
                bruh = db.execute(
                    "SELECT COUNT(*) FROM brought WHERE stock = ? AND username = ?;", stock, session["user_id"])
                huh = bruh[0]
                if huh == 0:
                    print("Hello")
                    db.execute("INSERT INTO brought (username, stock, amount) VALUES (?,?,?)",
                               session["user_id"], stock, shares)
                else:
                    print("Hi")
                    db.execute("UPDATE brought SET amount = amount + ? WHERE stock IS ?", shares, stock)
                db.execute("UPDATE users SET cash = ? WHERE id IS ?;",
                           money_used, session["user_id"])
                db.execute("INSERT INTO transactions (username, symbol, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'buy')",
                           session["user_id"], stock, shares, price)

                return apology("yay")

        else:
            return apology("Stock not found")



@app.route("/history")
@login_required
def history():

    transactions = db.execute(
        "SELECT symbol, shares, price, transaction_type, timestamp FROM transactions WHERE username = ? ORDER BY timestamp DESC", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        data = lookup(request.form.get("symbol"))
        if isinstance(data, dict):

            return render_template("quoted.html", info=data)
        else:
            return apology("Invalid Stock")
    else:
        return render_template("quotes.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("Username cannot be empty")

        if not password:
            return apology("Password cannot be empty")

        usernames = [row['username'] for row in db.execute("SELECT username FROM users;")]
        if username in usernames:
            return apology("User already exists")

        if password != confirmation:
            return apology("Passwords do not match")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username,
                   generate_password_hash(password, method='scrypt', salt_length=16))

        return render_template("index.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    else:
        shares = int(request.form.get("shares"))
        stock = request.form.get("symbol")
        data = lookup(stock)

        print(session["user_id"])
        money = int([row['cash'] for row in db.execute(
            "SELECT cash FROM users WHERE id IS ?; ", session["user_id"])][0])
        brought = db.execute(
            "SELECT stock, amount FROM brought WHERE username IS ?;", session["user_id"])
        stocks = set()
        for item in brought:
            stocks.add(item['stock'])

        unique_stocks = list(stocks)
        if stock in unique_stocks:
            brought_amount = db.execute(
                "SELECT stock, amount FROM brought WHERE username IS ? AND stock is ?;", session["user_id"], stock)
            total_amount = 0
            for item in brought_amount:
                total_amount += item['amount']
            if shares <= total_amount:
                price = data['price']
                money_earned = price * shares
                db.execute("UPDATE brought SET amount = amount - ? WHERE stock IS ?", shares, stock)
                db.execute("UPDATE users SET cash = cash + ? WHERE id IS ?",
                           money_earned,  session["user_id"])
                db.execute("INSERT INTO transactions (username, symbol, shares, price, transaction_type) VALUES (?, ?, ?, ?, 'sell')",
                           session["user_id"], stock, shares, price)

                return render_template("index.html")
            else:
                return apology("You do not own enough this stock")
        else:
            return apology("You do not own this stock")


@app.route("/money", methods=["GET", "POST"])
@login_required
def money():
    if request.method == "POST":
        amttoadd = int(request.form.get("money"))
        db.execute("UPDATE users SET cash = cash + ? WHERE id IS ?", amttoadd, session["user_id"])

        return render_template("index.html")
    return render_template("money.html")
