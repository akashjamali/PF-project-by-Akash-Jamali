About The Project:
The Disaster Rashan Distribution system is a comprehensive GUI-based desktop application developed in C language using the graphics.h library, designed to digitize and streamline the management of relief aid. Acting as a centralized database, the system begins with a secure admin login and transitions into a visual dashboard where administrators can register applicants by capturing personal details, income levels, and photos via a file browser. The core logic automatically determines eligibility—assigning specific "Rashan Packages" based on income thresholds and calculating "Bonus Bags" for government employees according to their pay grade—while storing all data persistently in a binary file (rashan_records.dat). Beyond registration, the system features a robust workflow that allows operators to track unique IDs, verify identities visually before marking supplies as "Handed Over," generate digital receipts, edit or delete records, and view real-time analytics including budget estimates and graphical distribution statistics, ensuring a transparent and efficient aid delivery process.

How it will word or compile: 
"This project is built using the C language. However, since setting up graphics.h for C in VS Code can be a bit tricky, you must save the file name as main.cpp (even though the code is in C) to avoid compilation errors. You will also need to configure the necessary libraries in VS Code for it to work.

To run the code, first enter the following compilation command in the terminal:

g++ main.cpp -o main.exe -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

Then run the executable:

.\main.exe

The code should now run without any errors. Since this is an admin-based project, you will need credentials to log in:

Username: admin

Password: admin

After logging in, make sure to input your data along with a picture. Please note that the image must be in JPEG or PNG format."
