"use strict"

let user = {name: "John"};

let p1 = {canView: true};
let p2 = {canEdit: true};

let clone = Object.assign({}, p1, p2);

alert(clone.canEdit);