from multiprocessing.sharedctypes import Value
import os

from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect,jsonify, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
import requests
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    """Show portfolio of stocks"""
    if request.method == "GET":
        user_id = session['user_id']
        
        cash_place = db.execute("SELECT cash FROM users WHERE id = ?",session['user_id'])
        cash_place = cash_place[0]['cash']
        cash_place = f"${cash_place:,.2f}".format(cash_place)
        
        result = db.execute("SELECT * FROM trans WHERE user_id = ?",session['user_id'])
        
        # iterate over all value comes from data base
        # and convert it to format string like 20.96546 to $20.96
        for i,v in enumerate(result):

            price_temp = v['price']
            new_price_temp = f"${price_temp:,.2f}".format(price_temp)
            result[i]['price'] = new_price_temp
            total_temp = v['total']
            
            new_total = f"${total_temp:,.2f}".format(total_temp)
            v['total'] = new_total

        CASH_TOTAL_PLACE = "$10.000.00"

        return render_template("index.html",value=result,total=CASH_TOTAL_PLACE,cash_place=cash_place)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    
    # GET
    if request.method == "GET":
        return render_template("buy.html") 
    
    # POST
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        
        # safety check
        if not symbol:
            return apology("Missing symbol")
        if not shares:
            return apology("Missing shares")
        
        # covert shares to int
        try:
            shares =  int(shares)
        except ValueError:
            return apology("Server Error",code=500)

        if shares < 0:
            return apology("Negative Number")

        
        # calling api
        symbol_call = lookup(symbol.upper())

        # make sure symbol is exists
        if symbol_call ==  None or not symbol_call:
            return apology("Invalid symbol")
        else:
            # get price of user input symbol
            price_symbol = symbol_call['price'] * shares
            
            # first check user money
            user_money = db.execute("""
            SELECT cash from users WHERE id = ?""",session['user_id'])
            
            # format cash
            user_money = user_money[0]['cash']


            # if user have enough money
            if user_money > price_symbol:
                
                # calculate new value of user cash 
                update_cash = user_money - price_symbol
                
                # update user cash
                db.execute("UPDATE users SET cash = ? WHERE id = ?",update_cash,session['user_id'])
                
                # register this transaction to trans data base
                time = datetime.now()
                # check for user is exits
                temp = db.execute("SELECT * FROM trans WHERE user_id = ? and symbol = ?",session['user_id'],symbol)
                
                # if user have not row add a new row for user
                if not temp or len(temp) == 0:
                    db.execute("""
                    INSERT INTO trans (user_id,symbol,name,shares,price,total,time)
                    VALUES (?, ?, ?, ?, ?, ?, ?)""",
                    session['user_id'],symbol_call['symbol'],
                    symbol_call['name'],shares,symbol_call['price'],price_symbol,time)
                    flash("bought! ")
                    return redirect("/")
                # if user have row update that row
                else:
                    # first get user correct shares
                    now_shares_user = db.execute("""
                    SELECT SUM(shares) AS sum FROM trans WHERE user_id = ? AND symbol = ?
                    """, session['user_id'],symbol)


                    now_shares_user = now_shares_user[0]['sum']
                    # added new share  to user share
                    now_shares_user += shares
                    
                    # update data base
                    db.execute("""
                    UPDATE trans SET shares = ? WHERE user_id = ? AND symbol = ?
                    """,now_shares_user, session['user_id'],symbol)
                    flash("Bought")
                    return redirect('/')
    
            else:
                # if user dost have enough money
                return apology("Not enough money")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    """Get stock quote."""
    
    # GET
    if request.method == "GET":
        return render_template("quote.html")
    
    # POST
    if request.method == "POST":
        symbol = request.form.get("quote")
        
        if not symbol:
            return apology("MIssing symbol",code=400)
        
        # calling api for symbol
        res = lookup(symbol)
        
        if res == None:
            return apology("MIssing symbol",code=400)
        
        else:
            # FOrmat price of shares 
            # like 20.398898 to 20.39
            res['price'] = f"{res['price']:.2f}"
            return render_template("/quoted.html",value=res)




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # GET
    if request.method == "GET":
        return render_template("register.html")
    # POST
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        password_re = request.form.get('confirmation')
    
    # check for empty password or username
    if not username:
        return apology("Missing Username")
    if not password or not password_re:
        return apology("missing Password")
    # check for match of password
    if password != password_re:
        return apology("Passwords are not match")

    # check username is not duplicate
    res = db.execute("SELECT * FROM users WHERE username = ?",username)
    if res or len(res) != 0  : 
        return apology("Username is duplicate")
    
    # insert username and password in to data base
    res = db.execute("""
    INSERT INTO users (username,hash) VALUES (?, ?)  
    """,username,generate_password_hash(password))
    
    # flash user to registered complete
    flash("register is complete")

    # redirect user to login page
    return redirect('/login')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    
    # GET
    if request.method == "GET":

        # get all symbol of user
        res = db.execute("""SELECT symbol,shares FROM trans WHERE
         user_id = ? """,session["user_id"])
        
        symbol = []
        user_shares = {}

        for i,v in enumerate(res):
            temp = v['symbol']
            if temp not in symbol:
                symbol.append(temp)
            
            if temp in user_shares:
                user_shares[temp] += v['shares']
                pass
            else:
                user_shares[temp] = v['shares']

        return render_template("sell.html",value=symbol)

    if request.method == "POST":
        
        symbol_input = request.form.get("symbol")
        shares_input = request.form.get("shares")
        
        # check to symbol is correct
        temp = lookup(symbol_input)
        if not temp or temp == None:
            return apology("Invalid symbol :(")

        try:
            shares_input = int(shares_input)
        except ValueError:
            return apology("Share must be positive number")

        if shares_input < 0:
            return apology("Share must be positive number")
            
        # select share of user 
        res = db.execute("""
        SELECT SUM(shares) AS sum FROM trans WHERE symbol = ? AND user_id =?
         """,symbol_input,session['user_id'])
        res = res[0]['sum']

        if shares_input > res:
            return apology("Not enough shares")
        else:
            # update user from data base
            price_to_pay =  temp['price'] * shares_input
            db.execute("SELECT shares,")
            
            


        
