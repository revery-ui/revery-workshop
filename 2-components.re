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

let bird = (~y, ()) => {
  <Positioned top=y left=0>
    <Image
      src=Assets.Bird.image01
      width=Assets.Bird.width
      height=Assets.Bird.height
    />
  </Positioned>;
};

let ground = () => {
  <Positioned bottom=0 left=0>
    <Image
      src=Assets.Land.image
      width=Constants.width
      height=Assets.Land.height
      resizeMode=ImageResizeMode.Repeat
    />
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

let textStyle =
  Style.[
    fontFamily("Roboto-Regular.ttf"),
    fontSize(24.),
    color(Colors.white),
  ];

Playground.render(
  <Center>
    <ClipContainer
      width=Constants.width height=Constants.height color=Colors.green>
      <sky />
      <ground />
      <bird y=50 />
      <Text style=textStyle text="Hello!" />
    </ClipContainer>
  </Center>,
);
