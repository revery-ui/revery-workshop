open Revery;
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

Playground.render(
  <Center>
    <ClipContainer
      width=Constants.width height=Constants.height color=Colors.green>
      React.empty
    </ClipContainer>
  </Center>,
);
