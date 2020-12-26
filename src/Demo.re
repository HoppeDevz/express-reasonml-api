open Express;
let app = express();
let serverPORT = 30120
let stringServerPort = "30120"

let onListen = e =>
  switch (e) {
  | exception (Js.Exn.Error(e)) =>
    Js.log(e);
    Node.Process.exit(1);
  | _ => Js.log @@ "Listening at http://127.0.0.1:" ++ stringServerPort
};

let makeSuccessJson = () => {
    let json = Js.Dict.empty();
    Js.Dict.set(json, "success", Js.Json.string("Hello World!"));
    Js.Json.object_(json);
};

App.get(app, ~path="/reason") @@
Middleware.from((next, req) => {
    Response.sendJson(makeSuccessJson());
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

let server = App.listen(app, ~port=serverPORT, ~onListen, ());

/*

type person = {
    firstname: string,
    lastname: string,
    age: int,
}

let myPerson:person = {
    firstname: "Gabriel",
    lastname: "Hoppe",
    age: 17
}

let myList = [1,2,3];
let myint:int = 20;
let mystring:string = "My String";

let listToArray = list => Array.of_list(list);
let print = value => Js.log(value);
let incrementOne = (value:int) => Js.log(value + 1);

for (x in 0 to 10) {
    let y = x + 1;
    y |> Js.log;
}

let printFirstName = (person:person) => Js.log(person.firstname);

print(listToArray(myList));
myPerson |> printFirstName;

*/



