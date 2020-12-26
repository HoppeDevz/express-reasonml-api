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

let createTableAdminAccounts() => {
    
}