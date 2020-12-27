const { cons } = require("bs-platform/lib/js/list");
const express = require("express");
const mysql = require("mysql");

const connection = mysql.createPool({
    host: "localhost",
    user: "root",
    password: "",
    database: "reason_ml"
});

const app = express();
app.use(express.json());

app.get("/select/admin_user", (req, res) => {
    var { username } = req.headers;
    username = username.replace(/"/g, "");
    console.log("username", username);
    connection.query(`SELECT * FROM admin_accounts WHERE username = '${username}'`, (error, results, fields) => {
        if (error) return res.status(500).send({ select: false, reason: "error", error });
        if (!results) return res.status(401).send({ select: false, reason: "bad_request" });
        console.log(results);
        if (results.length == 0) return res.status(200).send(false);
        return res.status(200).send(true);
    })
});

app.listen(40120, () => {
    console.log("Db server is running in port 40120")
})