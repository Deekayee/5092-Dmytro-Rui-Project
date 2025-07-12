# 🎥 Camera Shop Terminal App

> A simple yet effective terminal-based store management system, written in C++.

Developed with ❤️ by:  
[@Deekayee](https://github.com/Deekayee)  
[@xd4rk1ng](https://github.com/xd4rk1ng)

---

## 📦 About the Project

Camera Shop is a lightweight, terminal-driven application designed for managing a small retail camera store. It operates entirely via command-line and manages product stock, sales, clients, and reports—all from a single executable.

Upon first run, the program checks for a `stockList.csv`, `clientList.csv`, and `receiptList.csv` files in its folder. If any of the files are missing, a new blank file will be automatically created, ready for use.

---

## 🧭 Main Menu

You'll be greeted with several main options:

1. 🛒 **Shop Sales**
2. 📦 **Shop Stock**
3. 📑 **Reports**
4. 👥 **Clients**
5. 🚪 **Exit**

---

## 🛍️ Shop Sales

This module allows you to browse stock or manage your shopping cart. It includes two views:

- **Products View** – Displays all products available for purchase.
- **Cart View** – Shows all items currently in your cart.

### Available Options:

1. ➕ Add to Cart  
2. 🔁 Change Quantity in Cart  
3. ❌ Remove from Cart  
4. 🔄 Switch View (Products / Cart)  
5. 🧹 Clear Cart  
6. 💰 Checkout  
0. 🔙 Go Back

---

## 🏪 Shop Stock Management

The stock menu allows you to manage the store inventory.

### Available Options:

1. 🔍 Search Stock  
2. ➕ Add New Product  
3. ✏️ Edit Existing Product  
4. ❌ Remove Product  
0. 🔙 Go Back

---

## 👥 Clients Menu

This menu lets you manage customer data.

### Available Options:

1. 📝 Register New Client  
2. 💀 Kill (Disable) Client  
3. ♻️ Revive Client  
4. ✏️ Change Client Name  
5. 🔙 Exit

---

## 📑 Reports

Generate reports to analyze sales and inventory performance.

### Available Options:

1. 💰 Total Stock Value  
2. 📊 Sales Report by Product  
3. 📄 Complete Sales Report  
4. 🏆 Most Sold Product  
5. 🥄 Least Sold Product  
6. 👑 Top Client by Value  
0. 🔙 Go Back

---

## 🎉 Surprise Promotion (Gambling Feature™)

At checkout, you may get lucky and win **one random cart item for free!**  
Only our amazing clients have access to this feature.

---

## 📁 File Structure

- `stockList.csv` – Product stock database.
- `clientList.csv` – Client database.
- `receiptList.csv` – Sales database.

---

## 🚀 Getting Started

1. Clone the repository  
   ```bash
   git clone https://github.com/Deekayee/cameraShop.git
   cd cameraShop
   ```
2. Compile the program (example using `g++`)  
   ```bash
   g++ *.cpp -o shop.exe
   ```
3. Run it!  
   ```bash
   ./shop.exe
   ```
