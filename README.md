# Smart Retail POS System (Semester 1 Final Project)

A terminal-based Retail Management System built in C. This project simulates a real-world checkout experience for a tech store.

## ✨ Key Features
- **Stock Management:** Tracks inventory for products like Laptops and Smartphones.
- **Luhn Algorithm:** Validates credit card numbers (Visa, MasterCard, Amex) to ensure secure payments.
- **Dynamic Pricing:** Automatically applies discounts based on the payment method used.
- **Receipt Generation:** Appends transaction history to a local `receipts.txt` file.

## 🛠️ Technical Implementation
- **Data Structures:** Used `struct` to manage product data and stock.
- **Input Validation:** Implemented robust loops to handle incorrect user inputs.
- **File I/O:** Permanent storage of transaction logs.

## 🚀 How to Run
1. Compile the code: `gcc main.c -o pos_system`
2. Run the executable: `./pos_system`
