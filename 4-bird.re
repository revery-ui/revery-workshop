open Revery;
open Revery.Math;
open Revery.UI;
open Revery.UI.Components;

module Assets = {
  module Sky = {
    let height = 128;
    let width = 256;
    let image = "sky.png";
  };
  module Pipe = {
    let width = 90;
    let height = 480;
    let imageUp = "PipeUp.png";
    let imageDown = "PipeDown.png";
  };
  module Bird = {
    let height = 32;
    let width = 32;
    let image01 = "bird-01.png";
    let image02 = "bird-02.png";
    let image03 = "bird-03.png";
    let image04 = "bird-04.png";
  };
  module Land = {
    let image = "land.png";
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

let bird = (~children as _, ~y, ()) => {
  <Positioned top=y left=Constants.birdX>
    <Image
      src=Assets.Bird.image01
      width=Assets.Bird.width
      height=Assets.Bird.height
    />
  </Positioned>;
};

let ground = (~children as _, ~time, ()) => {
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

let sky = (~children as _, ()) => {
  <Positioned bottom=0 left=0>
    <Image
      src=Assets.Sky.image
      width=Constants.width
      height=Assets.Sky.height
      resizeMode=ImageResizeMode.Repeat
    />
  </Positioned>;
};

let textStyle =
  Style.[
    fontFamily("Roboto-Regular.ttf"),
    fontSize(24),
    color(Colors.white),
  ];

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

  type t = {
    bird: Bird.t,
    time: float,
  };

  let initialState: t = {bird: Bird.initialState, time: 0.};
  type action =
    | Flap
    | Step(float);

  let reducer = (action, state: t) =>
    switch (action) {
    | Flap => {...state, bird: Bird.flap(state.bird)}
    | Step(deltaTime) => {
        bird: Bird.applyGravity(deltaTime, state.bird),
        time: state.time +. deltaTime,
      }
    };
};

let world = {
  let component = React.component("world");

  (~children as _: list(React.syntheticElement), ()) =>
    component(hooks => {
      let (state, dispatch, hooks) =
        Hooks.reducer(~initialState=State.initialState, State.reducer, hooks);

      let hooks =
        Hooks.tick(
          ~tickRate=Seconds(0.),
          t => dispatch(Step(Time.toSeconds(t))),
          hooks,
        );

      (
        hooks,
        <Center>
          <View onMouseDown={_ => dispatch(Flap)}>
            <ClipContainer
              width=Constants.width
              height=Constants.height
              color=Colors.cornflowerBlue>
              <sky />
              <ground time={state.time} />
              <bird y={int_of_float(state.bird.position)} />
              <Text
                style=textStyle
                text={"Time: " ++ string_of_float(state.time)}
              />
            </ClipContainer>
          </View>
        </Center>,
      );
    });
};

Playground.render(<world />);
