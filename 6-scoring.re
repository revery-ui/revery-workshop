open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

module Assets = {
  module Sky = {
    let height = 128;
    let width = 256;
    let image = `File("sky.png");
  };
  module Pipe = {
    let width = 90;
    let height = 480;
    let imageUp = `File("PipeUp.png");
    let imageDown = `File("PipeDown.png");
  };
  module Bird = {
    let height = 32;
    let width = 32;
    let image01 = `File("bird-01.png");
    let image02 = `File("bird-02.png");
    let image03 = `File("bird-03.png");
    let image04 = `File("bird-04.png");
  };
  module Land = {
    let image = `File("land.png");
    let width = 256;
    let height = 32;
  };
};
module Constants = {
  let gravity = 2000.0;
  let floorHeight = 32;
  let flapForce = (-250.0);

  /* Speed (float) - horizontal speed of the flappy bird */
  let speedF = 100.;

  /* width (int) - the width of our 'game surface' */
  let width = 800;
  let height = 600;

  let birdX = 50;
  let pipeGap = 200;
};

let bird = (~y, ()) => {
  <Positioned top=y left=Constants.birdX>
    <Image
      src=Assets.Bird.image01
      width=Assets.Bird.width
      height=Assets.Bird.height
    />
  </Positioned>;
};

let ground = (~time, ()) => {
  let parallax =
    (-1.0)
    *. mod_float(time *. Constants.speedF, float_of_int(Assets.Land.width))
    |> int_of_float;
  <Positioned bottom=0 left=0>
    <Stack width=Constants.width height=Constants.floorHeight>
      <Positioned bottom=0 left=parallax>
        <Image
          src=Assets.Land.image
          width=Constants.width
          height=Assets.Land.height
          resizeMode=ImageResizeMode.Repeat
        />
      </Positioned>
      <Positioned bottom=0 left={parallax + Assets.Land.width}>
        <Image
          src=Assets.Land.image
          width=Constants.width
          height=Assets.Land.height
          resizeMode=ImageResizeMode.Repeat
        />
      </Positioned>
    </Stack>
  </Positioned>;
};

let sky = () => {
  <Positioned bottom=0 left=0>
    <Image
      src=Assets.Sky.image
      width=Constants.width
      height=Assets.Sky.height
      resizeMode=ImageResizeMode.Repeat
    />
  </Positioned>;
};

let fontRoboto = Font.Family.system("Roboto-Regular.ttf");
let textStyle = Style.[color(Colors.white)];

module State = {
  module Bird = {
    type t = {
      position: float,
      velocity: float,
      acceleration: float,
    };

    let minimumPosition =
      Constants.height
      - Assets.Land.height
      - Assets.Bird.height
      |> float_of_int;

    let initialState: t = {position: 300., velocity: 100., acceleration: 0.};

    let applyGravity = (time: float, bird: t) => {
      let velocity = bird.velocity +. bird.acceleration *. time;
      let acceleration = bird.acceleration +. Constants.gravity *. time;
      let position =
        min(minimumPosition, bird.position +. bird.velocity *. time);
      {position, velocity, acceleration};
    };

    let flap = (bird: t) => {
      {
        position: bird.position,
        velocity: Constants.flapForce,
        acceleration: 0.,
      };
    };
  };

  module Pipe = {
    type t = {
      top: Rectangle.t,
      bottom: Rectangle.t,
    };

    let create = (~x, ~height as h, ()) => {
      let width = Assets.Pipe.width |> float_of_int;
      let height = Assets.Pipe.height |> float_of_int;
      let almostRect = Rectangle.create(~x, ~width, ~height);

      let topY =
        float_of_int(Constants.height - Constants.pipeGap) -. h -. height;
      let bottomY = float_of_int(Constants.height) -. h;

      let top = almostRect(~y=topY);
      let bottom = almostRect(~y=bottomY);
      {top, bottom};
    };

    let getX = (pipe: t) => {
      Rectangle.getX(pipe.top);
    };

    let step = (t: float, pipe: t) => {
      let translate = Rectangle.translate(~x=Constants.speedF *. t *. (-1.));
      {top: translate(pipe.top), bottom: translate(pipe.bottom)};
    };

    let willCross = (deltaTime: float, pipe: t) => {
      let pipeMaxX = getX(pipe) +. float_of_int(Assets.Pipe.width);
      let birdMaxX = float_of_int(Constants.birdX + Assets.Bird.width);
      birdMaxX < pipeMaxX
      && birdMaxX > pipeMaxX
      -. deltaTime
      *. Constants.speedF;
    };

    let willCrossAny = (deltaTime: float, pipes: list(t)) => {
      List.exists(willCross(deltaTime), pipes);
    };
  };

  type t = {
    score: int,
    pipes: list(Pipe.t),
    bird: Bird.t,
    time: float,
  };

  let initialState: t = {
    score: 0,
    pipes: [],
    bird: Bird.initialState,
    time: 0.,
  };
  type action =
    | CreatePipe(float)
    | Flap
    | Step(float);

  let reducer = (action, state: t) =>
    switch (action) {
    | CreatePipe(height) =>
      let pipe = Pipe.create(~x=float_of_int(Constants.width), ~height, ());
      let pipes = [pipe, ...state.pipes];
      {...state, pipes};
    | Flap => {...state, bird: Bird.flap(state.bird)}
    | Step(deltaTime) => {
        score:
          Pipe.willCrossAny(deltaTime, state.pipes)
            ? state.score + 1 : state.score,
        pipes: List.map(Pipe.step(deltaTime), state.pipes),
        bird: Bird.applyGravity(deltaTime, state.bird),
        time: state.time +. deltaTime,
      }
    };
};

let pipe = (~pipe: State.Pipe.t, ()) => {
  let x = State.Pipe.getX(pipe) |> int_of_float;

  let topY = Rectangle.getY(pipe.top) |> int_of_float;
  let bottomY = Rectangle.getY(pipe.bottom) |> int_of_float;

  <Positioned top=0 left=x>
    <Stack width=Assets.Pipe.width height=Constants.height>
      <Positioned top=topY left=0>
        <Image
          src=Assets.Pipe.imageDown
          width=Assets.Pipe.width
          height=Assets.Pipe.height
        />
      </Positioned>
      <Positioned top=bottomY left=0>
        <Image
          src=Assets.Pipe.imageUp
          width=Assets.Pipe.width
          height=Assets.Pipe.height
        />
      </Positioned>
    </Stack>
  </Positioned>;
};

let%component world = () => {
  let%hook (state, dispatch) =
    Hooks.reducer(~initialState=State.initialState, State.reducer);

  let pipes =
    state.pipes |> List.map(p => <pipe pipe=p />) |> React.listToElement;

  let%hook () =
    Hooks.tick(~tickRate=Time.zero, t =>
      dispatch(Step(Time.toFloatSeconds(t)))
    );
  let%hook () =
    Hooks.tick(~tickRate=Time.seconds(4), _ =>
      dispatch(CreatePipe(Random.float(float_of_int(Assets.Pipe.height))))
    );

  <Center>
    <View onMouseDown={_ => dispatch(Flap)}>
      <ClipContainer
        width=Constants.width
        height=Constants.height
        color=Colors.cornflowerBlue>
        <sky />
        <ground time={state.time} />
        <View> ...pipes </View>
        <bird y={int_of_float(state.bird.position)} />
        <Text
          style=textStyle
          fontFamily=fontRoboto
          fontSize=24.
          text={"Score: " ++ string_of_int(state.score)}
        />
      </ClipContainer>
    </View>
  </Center>;
};

Playground.render(<world />);
