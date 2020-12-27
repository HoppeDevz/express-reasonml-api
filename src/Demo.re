open Express;
open Json;

let app = express();
let serverPORT = 30120
let stringServerPort = "30120"

Database.createDatabase();
Database.changeConnectionToDatabase();

module Decode = {
  open Json.Decode;
  let price = field("price", float);
  let obj = dict(price);
};

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ stringServerPort
};

let getDictString = (dict, key) =>
  switch (Js.Dict.get(dict, key)) {
  | Some(json) => Js.Json.decodeString(json)
  | _ => None
};

module Body = {
    type payload = {. "number": int};
    let jsonDecoder = json =>
      Json.Decode.({"number": json |> field("number", int)});
    let urlEncodedDecoder = dict => {
      "number": Js.Dict.unsafeGet(dict, "number") |> int_of_string,
    };
    let encoder = body =>
      Json.Encode.(object_([("number", body##number |> int)]));
};

App.get(app, ~path="/reason") @@
Middleware.from((next, req) => {
    let makeSuccessJson = () => {
        let json = Js.Dict.empty();
        Js.Dict.set(json, "success", Js.Json.string("Hello World!"));
        Js.Json.object_(json);
    };
    makeSuccessJson() |> Response.sendJson;
});

App.get(app, ~path="/hello") @@
Middleware.from((next, req) => {
    let myjson = () => {
        let json = Js.Dict.empty();
        Js.Dict.set(json, "success", Js.Json.string("Hello World!"));
        Js.Json.object_(json);
    }
    myjson() |> Response.sendJson;
});

App.post(app, ~path="/create_admin_user/:username/:password") @@
Middleware.from((next, req) => {
  let reqData = Request.params(req);
  let req_username: option(Js.Json.t) = Js.Dict.get(reqData, "username");
  let req_password: option(Js.Json.t) = Js.Dict.get(reqData, "password");

  switch (req_username, req_password) {
  | (Some(username), Some(password)) => Database.createAdminAccount(username, password)
  | _ => Js.log("None")
  }

  let myjson = (status: bool) => {
    let json = Js.Dict.empty();
    Js.Dict.set(json, "success", Js.Json.boolean(status));
    Js.Json.object_(json);
  }

  myjson(true) |> Response.sendJson;
    
});

let server = App.listen(app, ~port=serverPORT, ~onListen, ());



