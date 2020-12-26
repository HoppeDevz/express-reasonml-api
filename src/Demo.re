open Express;

let app = express();
let serverPORT = 30120
let stringServerPort = "30120"

/*Database.showDataBases();*/
Database.createDatabase();
Database.changeConnectionToDatabase();


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

App.post(app, ~path="/reasonpost/:id") @@
Middleware.from((next, req) => {
  let req_id = getDictString(Request.params(req), "id");
  let myjson = (status: bool) => {
    let json = Js.Dict.empty();
    Js.Dict.set(json, "success", Js.Json.boolean(status));
    Js.Json.object_(json);
  }

    let reqData = Request.params(req);
    switch (Js.Dict.get(reqData, "id")) {
    | Some(json) => Response.sendJson(myjson(true));
    | _ => Response.sendJson(myjson(false));
    }
    
});

let server = App.listen(app, ~port=serverPORT, ~onListen, ());



