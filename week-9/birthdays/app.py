import os
import sqlite3
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session



# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

# conn = sqlite3.connect('birthdays.db')
# db = conn.cursor()


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name =  request.form.get('Name')
        month =  request.form.get('Month')
        day =  request.form.get('Day')
        month = int(month)
        day = int(day)

        # TODO: Add the user's entry into the database
        db.execute('INSERT INTO birthdays (name,month,day) VALUES (?,?,?)',name,month,day)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        temp = db.execute('SELECT name,day,month from birthdays')

        names = []
        for name in temp:
            n = name['name']
            d = name['day']
            m = name['month']
            names.append((
                n , str(m) + '/' + str(d),
            ))
        return render_template("index.html",names=names)


