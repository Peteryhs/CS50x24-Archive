-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check crime scene reports
SELECT transcript
FROM interviews
WHERE year = 2023
AND month = 7
AND day in
(SELECT day FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = "Humphrey Street");
--Findings: Theif used ATM, went to Bakery, and Called  -- All of the same day of the crime, we can find dups to see who it is.
SELECT p.name, p.phone_number, p.license_plate
FROM people p
WHERE
    -- Person appears in bakery logs
    p.license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE year = 2023 AND month = 7 AND day = 28
    )
    -- Same person made a phone call
    AND p.phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE year = 2023 AND month = 7 AND day = 28
    )
    -- Same person made an ATM transaction
    AND p.id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number
            FROM atm_transactions
            WHERE year = 2023 AND month = 7 AND day = 28
        )
    );
-- Now that we got the people who matched the previous reqs, let see who made a qualifying phone called.
select name from people where phone_number in (select caller from phone_calls where duration < 60 and year = 2023 AND month = 7 AND day = 28);

-- The suspects are Bruce, Diana and Taylor. Let proceed to the airplane ticks
select name from people where passport_number in (select passport_number from passengers where flight_id in (select flight_id from flights where year = 2023 AND month = 7 AND day = 29));

--Looks like the same people are there, checking bakery logs
select name from people where license_plate in (select license_plate from bakery_security_logs where year = 2023 AND month = 7 AND day = 28);
-- Looks like its the same people again, lets see if their activies differ
SELECT p.name, b.activity, b.hour, b.minute
FROM people p
JOIN bakery_security_logs b
ON p.license_plate = b.license_plate
WHERE b.year = 2023
AND b.month = 7
AND b.day = 28;
-- Once again, there isnt much, they all arrived and left around the same time frame. However, we could check for their flight time, since the witeness said latest flight
SELECT p.name, f.hour, f.minute, air.city
FROM people p
JOIN passengers pass ON p.passport_number = pass.passport_number
JOIN flights f ON pass.flight_id = f.id
JOIN airports air ON f.destination_airport_id = air.id
WHERE f.year = 2023 AND f.month = 7 AND f.day = 29
AND p.name IN ('Diana', 'Taylor', 'Bruce')
ORDER BY f.hour, f.minute;

-- Looks like Bruce and Taylor is on the same flight headed for newyork city and is the earliest one. Base on them, lets check if their reciver has paid any large sum amnt of money to buy their ticket
-- Find their phone numbers
SELECT p.name, pc.duration, pc.receiver
   ...> FROM people p
   ...> JOIN phone_calls pc ON p.phone_number = pc.caller
   ...> WHERE pc.year = 2023 AND pc.month = 7 AND pc.day = 28
   ...> AND duration < 60
   ...> AND p.name IN ( 'Taylor', 'Bruce');
-- Find their names
select name from people where phone_number in (select receiver from phone_calls where receiver in ('(375) 555-8161', '(676) 555-6554'));
-- James, Robin, check their bank tranactions
SELECT atm_location, transaction_type, amount
FROM atm_transactions
WHERE account_number IN (
    SELECT account_number
    FROM bank_accounts
    WHERE person_id IN (
        SELECT id
        FROM people
        WHERE name IN ('James', 'Robin')
    )
);
-- None of them did anything, we hit a deadend, trying another way. Oh wait I missed a important detail, I didnt check the crime scene desc
SELECT street, description
FROM crime_scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';
-- Looks like the crime took place at 10:15, compare to their exit times (previous command)
-- Looks like Taylor left at 10:36 and Bruce at 10:18. To leave the parking lot 10 mins after the theft means you have to leave the bakery first, there fore Bruce would be the theif.
-- So, to sum up: Bruce stole the duck, and he boarded a flight escaping to NYC, and his compliance is Robin. :D

