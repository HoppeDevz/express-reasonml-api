// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Js_exn = require("bs-platform/lib/js/js_exn.js");
var Express = require("bs-express/src/Express.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Js_json = require("bs-platform/lib/js/js_json.js");
var Process = require("process");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");
var Caml_js_exceptions = require("bs-platform/lib/js/caml_js_exceptions.js");
var Database$MyNewProject = require("./Database.bs.js");

var app = Express.express(undefined);

var stringServerPort = "30120";

Database$MyNewProject.createDatabase(undefined);

Database$MyNewProject.changeConnectionToDatabase(undefined);

function onListen(e) {
  var val;
  try {
    val = e;
  }
  catch (raw_e){
    var e$1 = Caml_js_exceptions.internalToOCamlException(raw_e);
    if (e$1.RE_EXN_ID === Js_exn.$$Error) {
      console.log(e$1._1);
      return Process.exit(1);
    }
    throw e$1;
  }
  console.log("Listening at http://127.0.0.1:30120");
  
}

function getDictString(dict, key) {
  var json = Js_dict.get(dict, key);
  if (json !== undefined) {
    return Js_json.decodeString(Caml_option.valFromOption(json));
  }
  
}

function jsonDecoder(json) {
  return {
          number: Json_decode.field("number", Json_decode.$$int, json)
        };
}

function urlEncodedDecoder(dict) {
  return {
          number: Caml_format.caml_int_of_string(dict["number"])
        };
}

function encoder(body) {
  return Json_encode.object_({
              hd: [
                "number",
                body.number
              ],
              tl: /* [] */0
            });
}

var Body = {
  jsonDecoder: jsonDecoder,
  urlEncodedDecoder: urlEncodedDecoder,
  encoder: encoder
};

Express.App.get(app, "/reason", Express.Middleware.from(function (next, req) {
          var makeSuccessJson = function (param) {
            var json = {};
            json["success"] = "Hello World!";
            return json;
          };
          var partial_arg = makeSuccessJson(undefined);
          return function (param) {
            return Express.$$Response.sendJson(partial_arg, param);
          };
        }));

Express.App.get(app, "/hello", Express.Middleware.from(function (next, req) {
          var myjson = function (param) {
            var json = {};
            json["success"] = "Hello World!";
            return json;
          };
          var partial_arg = myjson(undefined);
          return function (param) {
            return Express.$$Response.sendJson(partial_arg, param);
          };
        }));

Express.App.post(app, "/create_admin_user/:username/:password", Express.Middleware.from(function (next, req) {
          var req_username = getDictString(Express.$$Request.params(req), "username");
          var req_password = getDictString(Express.$$Request.params(req), "password");
          var myjson = function (status) {
            var json = {};
            json["success"] = status;
            return json;
          };
          if (req_username !== undefined) {
            if (req_password !== undefined) {
              var partial_arg = myjson(true);
              return function (param) {
                return Express.$$Response.sendJson(partial_arg, param);
              };
            }
            var partial_arg$1 = myjson(false);
            return function (param) {
              return Express.$$Response.sendJson(partial_arg$1, param);
            };
          }
          var partial_arg$2 = myjson(false);
          return function (param) {
            return Express.$$Response.sendJson(partial_arg$2, param);
          };
        }));

var server = Express.App.listen(app, 30120, undefined, onListen, undefined);

var serverPORT = 30120;

exports.app = app;
exports.serverPORT = serverPORT;
exports.stringServerPort = stringServerPort;
exports.onListen = onListen;
exports.getDictString = getDictString;
exports.Body = Body;
exports.server = server;
/* app Not a pure module */
