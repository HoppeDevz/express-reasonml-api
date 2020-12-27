open Fetch;

let checkIfExistAdminUser = (username: string) => {
    Js.Promise.(
    Fetch.fetchWithInit(
        "http://localhost:40120/select/admin_user",
        Fetch.RequestInit.make(
            ~headers=
            Fetch.HeadersInit.makeWithArray([|
                ("username", username)
            |]),
            ~method_=Get,
            ()
        )
    )
        |> then_(Fetch.Response.json)
        |> then_(json => json |> resolve)
    );
};

/*let res = checkIfExistAdminUser("gabrielh2c");

let prms = Js.Promise.(
    res |> then_(json => Js.log(json) |> resolve)
)*/