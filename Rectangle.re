open Revery.Math;

type t = BoundingBox2d.t;

let create = (~x, ~y, ~width, ~height) =>
  BoundingBox2d.create(x, y, x +. width, y +. height);

let getX = rect => {
  let (x, _, _, _) = BoundingBox2d.getBounds(rect);
  x;
};

let getY = rect => {
  let (_, y, _, _) = BoundingBox2d.getBounds(rect);
  y;
};

let translate = (~x=0., ~y=0., rect) =>
  BoundingBox2d.transform(rect, Skia.Matrix.makeTranslate(x, y));

let intersects = BoundingBox2d.intersects;
