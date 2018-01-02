open UniversalRouter;

let handlers = () => [|
  route(~path="/", ~action=() => Js.Promise.resolve("Home"), ()),
  route(~path="/about", ~action=() => Js.Promise.resolve("About"), ())
|];