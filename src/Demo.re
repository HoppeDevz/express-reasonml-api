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

App.post(app, ~path="/create_admin_user/:username/:password") @@
Middleware.from((next, req) => {
  let reqData = Request.params(req);
  let req_username: option(Js.Json.t) = Js.Dict.get(reqData, "username");
  let req_password: option(Js.Json.t) = Js.Dict.get(reqData, "password");

  let myjson = (status: bool) => {
    let json = Js.Dict.empty();
    Js.Dict.set(json, "created_user", Js.Json.boolean(status));
    Js.Json.object_(json);
  }

  let created_user_ = ref(false)

  switch (req_username, req_password) {
  | (Some(username), Some(password)) => Database.createAdminAccount(username, password, (created_user: bool) => {
      created_user_.contents = created_user;
    })
  }

  myjson(created_user_^) -> Response.sendJson;
  
});

let server = App.listen(app, ~port=serverPORT, ~onListen, ());



