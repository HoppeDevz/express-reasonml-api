// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Fetch = require("bs-fetch/src/Fetch.bs.js");
const fetch = require("node-fetch");

function checkIfExistAdminUser(username) {
  return fetch("http://localhost:40120/select/admin_user", Fetch.RequestInit.make(/* Get */0, [[
                          "username",
                          username
                        ]], undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(undefined)).then(function (prim) {
                return prim.json();
              }).then(function (json) {
              return Promise.resolve(json);
            });
}

exports.checkIfExistAdminUser = checkIfExistAdminUser;
/* No side effect */
