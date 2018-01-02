type t;

[@bs.obj]
external route :
  (
    ~path: string,
    ~name: string=?,
    ~children: array(Js.t({..}))=?,
    ~action: unit => Js.Promise.t('a)=?,
    unit
  ) =>
  t =
  "";

[@bs.module] [@bs.new]
external router : array('routes) => t = "universal-router";

[@bs.send.pipe : 't]
external resolve : Js.t({..}) => Js.Promise.t('a) = "resolve";