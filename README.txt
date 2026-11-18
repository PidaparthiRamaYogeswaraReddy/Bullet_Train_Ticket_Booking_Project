BULLET TRAIN TICKET BOOKING SYSTEM - MODULAR C PROJECT

FILES
main.c              Main menu and program entry point
railway.h           Shared structures, constants and function declarations
common.c            Shared booking storage, file handling, input and date utilities
module1_train.c     Train master data, station data, train search and route calculations
module2_booking.c   Passenger registration, seat inventory, fare calculation and booking
module3_ticket.c    PNR generation, ticket printing, search, history and modification
module4_admin.c     Cancellation, refund, admin login, reports and fare updates

BUILD ON macOS (from this folder)
clang -std=c99 -Wall -Wextra main.c common.c module1_train.c module2_booking.c module3_ticket.c module4_admin.c -o railway
./railway

ADMIN LOGIN
ID: admin
Password: 1234

TEAM RESPONSIBILITIES
Member 1: Module 1 - Train & Route
Member 2: Module 2 - Passenger & Booking
Member 3: Module 3 - Ticket & PNR
Member 4: Module 4 - Cancellation & Admin

common.c contains only shared infrastructure: global booking storage, file persistence,
input helpers and date validation. The domain-specific logic belongs to each module.

NOTES
- bookings.dat is created in the working directory to store booking records.
- Keep bookings.dat if you want to preserve your test bookings.
- Approximate segment distances and the 80% refund are demonstration assumptions,
  not official railway data or policy.
- Delhi-to-Chennai sample station timings use the supplied schedule; reverse timings
  are illustrative.
