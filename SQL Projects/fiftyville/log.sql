-- Take a look at the crime reports that happened in July 28th.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28;

-- Take a look at the bakery security logs around the time of the crime 10:15am.
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE month = 7 AND day = 28 AND hour = 10;

-- Take a look at the 3 interviews that where mentioned in the crime report.
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28;
/*
Now I have to check 3 things:
    1. The bakery security logs 10 minutes before the crime
    2. The transactions of the atm somewhere on Leggett Street before the time of the crime
    3. The small (less than a minute) phone calls that happened that day
*/

-- Check the bakery security logs again.
SELECT hour, minute, activity, license_plate
FROM bakery_security_logs
WHERE month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25   -- The cars which license plates are 6P58WS2, G412CB7 entered and left the bakery around the time of the theft which is sus

-- Check the ATM transactions the day of the crime earlier (the withdraw ones only).
SELECT *
FROM atm_transactions
WHERE month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location LIKE '%Leggett Street%'; -- The multiple account numbers that I got are sus..

-- Check out the phone calls.
SELECT caller, receiver, duration
FROM phone_calls
WHERE month = 7
AND day = 28
AND duration < 60; --Welp, these numbers which I got are sus too..

-- Investigate the earliest flight on the next day.
SELECT *
FROM flights
WHERE month = 7
AND day = 29
ORDER BY hour ASC, minute ASC
LIMIT 1;    -- The flight ID is 36, going from airport (8) --> airport (4), this might help us later..

-- Get information (passport numbers) of every person that flight.
SELECT passport_number
FROM passengers
WHERE flight_id IN
    (SELECT id
    FROM flights
    WHERE month = 7
    AND day = 29
    ORDER BY hour ASC, minute ASC
    LIMIT 1);   -- flight ID = 36

/*
Here I got the idea of gathering all these pieces of information together,
and trying to find a suspect from the TABLE People.
*/

-- But first let me take a quick look at people.
SELECT * FROM people LIMIT 20; -- Just a small amount would be enough to illustrate.

-- Now let me join these tables together and find the person that we are looking for.
SELECT DISTINCT(p.name)

FROM people AS p
JOIN bank_accounts AS b
    ON p.id = b.person_id
JOIN bakery_security_logs
    ON p.license_plate = bakery_security_logs.license_plate
JOIN passengers
    ON p.passport_number = passengers.passport_number

WHERE bakery_security_logs.license_plate IN
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25)

AND b.person_id IN
    (SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND transaction_type = 'withdraw'
        AND atm_location LIKE '%Leggett Street%'))

AND passengers.passport_number IN
    (SELECT passport_number
    FROM passengers
    WHERE flight_id IN
        (SELECT id
        FROM flights
        WHERE month = 7
        AND day = 29
        ORDER BY hour ASC, minute ASC
        LIMIT 1))

AND (p.phone_number IN
        (SELECT caller
    FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND duration < 60)
    OR p.phone_number IN
        (SELECT receiver
    FROM phone_calls
    WHERE month = 7
    AND day = 28
    AND duration < 60)
    );      -- From the previous Query, we Find that the Thief's name is Bruce!

-- Now we knew the thief's name, it's time to capture his accomplice, by getting the name of the person he called.
SELECT name FROM people
WHERE phone_number IN
    (SELECT receiver FROM phone_calls
    WHERE caller IN
        (SELECT phone_number FROM people
        WHERE name = 'Bruce')
    AND month = 7
    AND day = 28
    AND duration < 60);     -- And it turns out, that his accomplice is Robin!

-- Finally we need to find out where the thief has escaped to.
SELECT city FROM airports
WHERE id IN
    (SELECT destination_airport_id FROM flights
    WHERE id IN
        (SELECT flight_id FROM passengers
        WHERE passport_number IN
            (SELECT passport_number FROM people
            WHERE name = 'Bruce')));    -- He escaped to New York!

--CASE SOLVED!!!!
