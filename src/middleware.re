type asyncMiddleware =
  (Express.Request.t, Express.Response.t, Express.Next.t) =>
  Js.Promise.t(Express.done_);

external asyncMiddlewareFrom : asyncMiddleware => Express.Middleware.t =
  "%identity";

let app = Express.App.make();

module Status = {
  let make = () =>
    asyncMiddlewareFrom((_req, res, _next) =>
      Js.Promise.resolve(Express.Response.sendString(res, "works"))
    );
};

module App = {
  let make = () =>
    asyncMiddlewareFrom((req, res, _next) => {
      let universalRouter = UniversalRouter.router(Routes.handlers());
      universalRouter
      |> UniversalRouter.resolve({"pathname": Express.Request.path(req)})
      |> Js.Promise.then_(result => {
           let render = () => Express.Response.sendString(res, result);
           Js.Promise.resolve(render());
         });
    });
};