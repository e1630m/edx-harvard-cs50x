-- Keep a log of any SQL queries you execute as you solve the mystery.
-- 1. Starts with .schema
.schema
-- Output snipped

-- 2. Look for a crime which took place on Chamberlin Street on July 28, 2020
SELECT description
  FROM crime_scene_reports
 WHERE year = '2020'
   AND month = '7'
   AND day = '28'
   AND street = 'Chamberlin Street';
-- Output
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- 3. Search for the transcript of interviews on July 28, 2020 which mentions the courthouse
SELECT id, name, transcript
  FROM interviews
 WHERE year = '2020'
   AND month = '7'
   AND day = '28'
   AND transcript LIKE '%courthouse%';
-- Output
-- 161|Ruth   |Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
--             If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- 162|Eugene |I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
--             I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- 163|Raymond|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
--             In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--             The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 4. Follow the lead from Ruth
SELECT hour, minute, people.license_plate, activity, phone_number, passport_number, name
  FROM courthouse_security_logs
       JOIN people
       ON courthouse_security_logs.license_plate = people.license_plate
 WHERE year = '2020'
   AND month = '7'
   AND day = '28'
   AND hour = '10'
   AND '15' <= minute AND minute <= '25';
-- Output
-- 10|16|5P2BI95|exit|(725) 555-4692|2963008352|Patrick
-- 10|18|94KL13X|exit|(367) 555-5533|5773159633|Ernest
-- 10|18|6P58WS2|exit|(301) 555-4174|7526138472|Amber
-- 10|19|4328GD8|exit|(389) 555-5198|8496433585|Danielle
-- 10|20|G412CB7|exit|(130) 555-0289|1695452385|Roger
-- 10|21|L93JTIZ|exit|(829) 555-5269|7049073643|Elizabeth
-- 10|23|322W7JE|exit|(770) 555-1861|3592750733|Russell
-- 10|23|0NTHK55|exit|(499) 555-9472|8294398571|Evelyn

-- 5. Follow the lead from Eugene and compare it to Ruth's
SELECT bank_accounts.account_number, transaction_type, amount,
       people.id, license_plate, phone_number, passport_number, name
  FROM atm_transactions
       JOIN bank_accounts
       ON atm_transactions.account_number = bank_accounts.account_number

       JOIN people
       ON bank_accounts.person_id = people.id
 WHERE atm_location = 'Fifer Street'
   AND year = '2020'
   AND month = '7'
   AND day = '28'
   AND transaction_type = 'withdraw'
   AND license_plate IN
       (SELECT people.license_plate
          FROM courthouse_security_logs
               JOIN people
               ON courthouse_security_logs.license_plate = people.license_plate
         WHERE year = '2020'
           AND month = '7'
           AND day = '28'
           AND hour = '10'
           AND '15' <= minute AND minute <= '25');
-- Output
-- 49610011|withdraw|50|686048|94KL13X|(367) 555-5533|5773159633|Ernest
-- 26013199|withdraw|35|514354|322W7JE|(770) 555-1861|3592750733|Russell
-- 25506511|withdraw|20|396669|L93JTIZ|(829) 555-5269|7049073643|Elizabeth
-- 28500762|withdraw|48|467400|4328GD8|(389) 555-5198|8496433585|Danielle

-- 6. Follow the lead from Raymond
SELECT name, passport_number
  FROM phone_calls
       JOIN people
       ON caller = phone_number
 WHERE year = '2020'
   AND month = '7'
   AND day = '28'
   AND duration <= '60'
   AND caller IN (
       SELECT phone_number
         FROM atm_transactions
              JOIN bank_accounts
              ON atm_transactions.account_number = bank_accounts.account_number

              JOIN people
              ON bank_accounts.person_id = people.id
        WHERE atm_location = 'Fifer Street'
          AND year = '2020'
          AND month = '7'
          AND day = '28'
          AND transaction_type = 'withdraw'
          AND license_plate IN
              (SELECT people.license_plate
                 FROM courthouse_security_logs
                      JOIN people
                      ON courthouse_security_logs.license_plate = people.license_plate
                WHERE year = '2020'
                  AND month = '7'
                  AND day = '28'
                  AND hour = '10'
                  AND '15' <= minute AND minute <= '25'))
INTERSECT
SELECT name, people.passport_number
  FROM passengers
       JOIN people
       ON passengers.passport_number = people.passport_number
 WHERE flight_id = (
       SELECT flights.id
         FROM airports
              JOIN flights
              ON airports.id = flights.origin_airport_id
        WHERE year = '2020'
          AND month = '7'
          AND day = '29'
          AND city = 'Fiftyville'
        ORDER BY hour ASC
        LIMIT 1);
-- Output
-- Ernest|5773159633 (Thief identified)

-- 7. Find the destination city of the flight
SELECT city
  FROM airports
 WHERE id = (
       SELECT flights.destination_airport_id
         FROM airports
              JOIN flights
              ON airports.id = flights.origin_airport_id
        WHERE year = '2020'
          AND month = '7'
          AND day = '29'
          AND city = 'Fiftyville'
        ORDER BY hour ASC
        LIMIT 1);
-- Output
-- London (Destination identified)

-- 8. Find the accomplice
SELECT name, receiver
  FROM phone_calls
       JOIN people
       ON receiver = phone_number
 WHERE year = '2020'
   AND month = '7'
   AND day = '28'
   AND duration <= '60'
   AND caller = '(367) 555-5533';
-- Output
-- Berthold|(375) 555-8161 (Accomplice identified)
