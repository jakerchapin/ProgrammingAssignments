#This was done in Fall 2014.

#!/usr/bin/python
#
# This program allows for viewing account info and history, as well as
# adding transactions.
#
import sys
import os
import datetime
import shutil
from operator import itemgetter
# Make sure an argument was passed to the program.
try:
        gotdata = sys.argv[1]
except IndexError:
        print "A command must be entered with this program, like so:\n./accounts
.py [command]\nFor a list of commands and what they do, enter the following:\n./
accounts.py -?"
        exit()
# Information given from -? command
if sys.argv[1] == "-?":
        print "This program allows for viewing account info and history as well 
as adding\ntransactions.\nThe program reads data from the file assigned to the v
ariable ACCT_LIST.\nThe following is a list of commands that can be used:\n-i  -
h  -t\n-i -- Account info\nDisplays the number, holder's name, and balance of th
e chosen account.\n-h -- History\nDisplays all transactions for the chosen accou
nt in chronological order.\n-t -- Insert transaction\nWithdraw from or deposit t
o an account, or create a new account."
        exit()
# Get input file, give meaningful error message in case of failure.
try:
        infile = file(os.environ['ACCT_LIST'])
except KeyError:
        print "Error: No input file assigned to variable ACCT_LIST"
        exit()
# Create data structures to use later
transaction_list = []
account_list = []
account_dict = {}
# Make the transaction list
for line in infile:
        transaction_data = line.split(':')
        transaction_list.append(transaction_data)
# Make the account list
for element in transaction_list:
        account_list.append(element[1] + " " + element[0])
# Make the sorted account set
account_set = sorted(set(account_list))
# Make the account dictionary
i = 1
for element in account_set:
        account_dict[i] = element
        i += 1
# -i command
if sys.argv[1] == "-i":
# Establish menu loop
        user_choice = "y"
        while user_choice != 'q':
# Display menu
                n = 1
                for element in account_set:
                        print "%d. %s" % (n, element)
                        n += 1
# Get user's choice and manage input errors
                try:
                        account_choice = input("Enter the list (left) number of 
the account you want info on.\nTo exit, enter q. ")
                except NameError:
                        print "Exiting."
                        exit()
                while account_choice < 1 or account_choice > n:
                        try:
                                account_choice = input( "Invalid number. Please 
enter one of the numbers on the left.\nIf you wish to exit, enter q. ")
                        except NameError:
                                print "Exiting."
                                exit()
# Print basic account info
                account_info  = account_dict[account_choice].split(' ')
                print "Account holder: %s %s" % (account_info[0], account_info[1
])
                print "Account number: %s" % (account_info[2])
# Get and print balance
                balance = 0.0
                for element in transaction_list:
                        if element[0] == account_info[2]:
                                if element[3] == 'W':
                                        transaction = element[4].split('\n')
                                        balance -= float(transaction[0])
                                else:
                                        transaction = element[4].split('\n')
                                        balance += float(transaction[0])
                print "Balance: %d" % (balance)
# Prompt to quit or return to menu
                user_choice = raw_input("To exit, enter q. To continue, just pre
ss enter." )
        print "Exiting."
        exit()
# -h command
elif sys.argv[1] == "-h":
# Display menu
        n = 1
        for element in account_set:
                print "%d. %s" % (n, element)
                n += 1
# Get user's choice and manage input errors
        try:
                account_choice = input("Enter the list (left) number of the acco
unt you want the history of.\nTo exit, enter q. ")
        except NameError:
                print "Exiting."
                exit()
        while account_choice < 1 or account_choice > n:
                try:
                        account_choice = input("Invalid number. Please enter one
 of the numbers on the left.\nIf you wish to exit, enter q. ")
                except NameError:
                        print "Exiting."
                        exit()
# Get account history
        account_info = account_dict[account_choice].split(' ')
        account_number = account_info[2]
        for element in transaction_list:
                if element[0] == account_number:
                        transaction = element[4].split('\n')
                        if element[3] == 'W':
                                print "%s: Withdrew $%s" % (element[2], transact
ion[0])
                        else:
                                print "%s: Deposited $%s" % (element[2], transac
tion[0])
        exit()
# -t command
elif sys.argv[1] == "-t":
# Establish menu loop
        user_choice = 'y'
        while user_choice != 'q':
# Display menu
                n = 1
                for element in account_set:
                        print "%d. %s" % (n, element)
                        n += 1
                user_choice = raw_input("Enter the list (left) number of the acc
ount you want to make a transaction\nwith. If you want to add a new account, ent
er a.\nTo exit, enter q. ")
                if user_choice == 'q':
                        print "Exiting."
                        exit()
# Create a new account
                elif user_choice == 'a':
# Make sure chosen account number is not in use
                        number_list = []
                        for element in transaction_list:
                                number_list.append(element[0])
                        accountnumber = 'invalid'
                        while accountnumber == 'invalid':
                                new_account = input("Enter the desired 4-digit a
ccount number. (0000-9999) ")
                                while new_account < 0 or new_account > 9999:
                                        print "Invalid account number. Account n
umber must be 4 digits. (0000-9999)"
                                        new_account = input("Enter the desired 4
-digit account number. (0000-9999) ")
                                new_account = str(new_account)
                                if new_account in number_list:
                                        print "Account number already in use. Ch
oose a different number."
                                else:
                                        accountnumber = 'valid'
# Add name
                        name = raw_input("Enter your first and last name. ")
                        new_account = new_account + ":" + name + ":"
# Add date
                        date = str(datetime.date.today())
                        new_date = date.split("20")
                        date = new_date[1]
                        new_date = date.split("-")
                        new_account = new_account + new_date[0] + "." + new_date
[1] + "." + new_date[2] + ":"
# Deposit or withdraw
                        d_or_w = 'n'
                        while d_or_w != 'd' and d_or_w != 'w':
                                d_or_w = raw_input("Deposit or withdraw? Choose 
by entering d or w. ")
                                if d_or_w != 'd' and d_or_w != 'w':
                                        print "Please enter d or w."
                        if d_or_w == 'd':
                                new_account = new_account + "D:"
                        else:
                                new_account = new_account + "W:"
# Amount to deposit or withdraw
                        amount = input("Enter the amount of money you want to de
posit or withdraw. ")
                        new_amount = str(amount)
                        new_account = new_account + new_amount + "\n"
# Backup and then update database
                        shutil.copyfile(os.environ['ACCT_LIST'], 'backup.db')
                        database = open(os.environ['ACCT_LIST'], 'a')
                        database.write(new_account)
                        database.close()
# Prompt to continue operations or exit
                        user_choice = raw_input("To exit, enter q. To continue o
perations, just press enter." )
                        if user_choice == 'q':
                                print "Exiting."
                                exit()
                        else:
# Update account list
                                account_list_update = new_account.split(":")
                                account_list.append(account_list_update[1] + " "
 + account_list_update[0])
                                account_set = sorted(set(account_list))
                                i += 1
                                account_dict[i] = (account_list_update[1] + "_" 
+ account_list_update[0])
                else:
# New transaction for existing account
                        account_choice = int(user_choice)
                        while account_choice < 0 or account_choice > n:
                                account_choice = input("Invalid account selectio
n. Please enter one of the list numbers. ")
# Get data on current account
                        account_info  = account_dict[account_choice].split(' ')
                        new_transaction = account_info[2] + ":" + account_info[0
] + " " + account_info[1] + ":"
# Add date
                        date = str(datetime.date.today())
                        new_date = date.split("20")
                        date = new_date[1]
                        new_date = date.split("-")
                        new_transaction = new_transaction + new_date[0] + "." + 
new_date[1] + "." + new_date[2] + ":"
# Deposit or withdraw
                        d_or_w = 'n'
                        while d_or_w != 'd' and d_or_w != 'w':
                                d_or_w = raw_input("Deposit or withdraw? Choose 
by entering d or w. ")
                                if d_or_w != 'd' and d_or_w != 'w':
                                        print "Please enter d or w."
                        if d_or_w == 'd':
                                new_transaction = new_transaction + "D:"
                        else:
                                new_transaction = new_transaction + "W:"
# Amount to deposit or withdraw
                        amount = input("Enter the amount of money you want to de
posit or withdraw. ")
                        new_amount = str(amount)
                        new_transaction = new_transaction + new_amount + "\n"
# Backup and then update database
                        shutil.copyfile(os.environ['ACCT_LIST'], 'backup.db')
                        database = open(os.environ['ACCT_LIST'], 'a')
                        database.write(new_transaction)
                        database.close()
# Prompt to exit or continue operations
                        user_choice = raw_input("To exit, enter q. To continue, 
just press enter. ")
                        if user_choice == 'q':
                                print "Exiting."
                                exit()
                        else:
# Update transaction list
                                transactionlist_update = new_transaction.split("
:")
                                transaction_list.append(transactionlist_update)
else:
# Give meaningful error if invalid command is given
        print "Invalid command. Valid commands: -i  -h  -t  -?"
        exit()
