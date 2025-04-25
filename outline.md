## Camera shop

Simple cli c++ program, that helps managing a camera shop, purchases, sales and stock management.

#### Must use concepts
- Functions
- Arrays
- Matrix
- Pointers

##### Data structure:
###### Stock
- int stockId (autoincrement, think about how to deal with ids if their entry was deleted)
- string productName
- int quantity
- double costValue
- double saleValue (derived value)

###### CartItem
- int stockId
- int quantity
- double saleWithoutTax
- double taxRatePercent
- string productName

###### Receipt
- int receiptId (autoincrement)
- int clientId (autoincrement)
- double paymentAmount
- string date (grabs current time stamp)
- double costWithTax (derived value)
- double totalCost (derived value)

##### Needed functions:
 - create database file if it doesn’t exist
 - write to db file (when we do any alterations to the stock)
 - purchase a product to add it to stock
 - show stock
 - show stock to buyer (show sale value)
 - after show stock, ask user to input desired product id to buy, ask for quantity, ask if wants to buy more products (do while yes)
 - checkout function that shows added to cart items, ask for confirmation, ask user to input payment value and output receipt
 - save receipt to file
 - edit data (change quantity on sales and purchases)
 - delete data (if quantity zeroed during a sale or we just want to delete a product) not sure

##### Menu structure

Shop menu:
1. Shop Sales
	1. Sales menu
		1. Show products
			1. Input id of product to add to cart (repeats)
				1. Checkout
					1. Confirm (show/save receipt)
					2. Go back
				2. Go back 
			2. Go back (clears the cart as well)
	2. Go back
2. Shop Stock
	1. Show stock
		1. Purchase stock
		2. Remove stock
			1. Input id of product to remove
			2. Go back
	2. Go back
3. Exit