open MySql2;

let connection = ref(MySql2.Connection.connect(~host="127.0.0.1", ~port=3306, ~user="root", ()));
let con = connection.contents;

let showDataBases = () => {
    MySql2.execute(con, "SHOW DATABASES", None, res => {
        switch res {
        | `Error(e) => Js.log2("ERROR: ", e)
        | `Select(select) => Js.log2("SELECT: ", select)
        | `Mutation(mutation) => Js.log2("MUTATION: ", mutation)
        }
    });
}

let createDatabase = () => {
    MySql2.execute(con, "CREATE DATABASE IF NOT EXISTS reason_ml", None, res => {
        switch res {
        | `Error(e) => Js.log2("ERROR: ", e)
        | _ => Js.log("[DATABASE] CREATED DATABASE reason_ml")
        }
    });
}

let changeConnectionToDatabase = () => {
    connection := MySql2.Connection.connect(~host="127.0.0.1", ~port=3306, ~user="root", ~password="", ~database="reason_ml", ());
    Js.log("[DATABASE] NEW CONNECTION STATUS, CHANGE TO reason_ml DATABASE");
}

let createAdminAccountsTable = () => {
    let sql = "CREATE TABLE admin_accounts (
        id int(11) NOT NULL AUTO_INCREMENT,
        username varchar(255) NOT NULL,
        password varchar(512) NOT NULL,
        PRIMARY KEY(id)
    )"
    MySql2.execute(connection^, sql, None, res => {
        switch(res) {
        | `Error(e) => Js.log2("ERROR: ", e)
        | _ => Js.log("[DATABASE] CREATED TABLE admin_accounts")
        }
    });
}

let createAdminAccount = (username: Js.Json.t, password: Js.Json.t, callback) => {
    let named = MySql2.Params.named(
        Json.Encode.object_([
            ("username", username),
            ("password", password),
        ])
    );

    let register = value => {
        let stringify_value = Js.Json.stringify(value);

        switch (stringify_value == "true") {
        | false => MySql2.execute(connection^, "INSERT INTO admin_accounts (username, password) VALUES(:username, :password)", Some(named), res => callback(true))
        | true => callback(false)
        }

    }

    let username_string = Js.Json.stringify(username);
    let req = MyRequest.checkIfExistAdminUser(username_string);

    let promise = Js.Promise.(
        req
        |> then_(json => resolve(json -> register))
    )

}