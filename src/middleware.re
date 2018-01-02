type asyncMiddleware =
  (Express.Request.t, Express.Response.t, Express.Next.t) =>
  Js.Promise.t(Express.done_);

external asyncMiddlewareFrom : asyncMiddleware => Express.Middleware.t =
  "%identity";

module Status = {
  let app = Express.App.make();
  let make = () =>
    asyncMiddlewareFrom((_req, res, _next) =>
      Js.Promise.resolve(Express.Response.sendString(res, "works"))
    );
};

module App = {
  let app = Express.App.make();
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