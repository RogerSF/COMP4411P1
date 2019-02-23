# COMP4411P1 Impressionist

### TODOs:

Basics:
- [X] Implement 5 different brush types:
  - [X] single line
  - [X] (filled) circles
  - [X] scattered points
  - [X] scattered lines
  - [X] scattered (filled) circles
  - Note that scattered brushes should sample from each location they color individually, not just use a single color for each splotch.
  
- [X] Add sliders to control various brush attributes. You need to include sliders for the line thickness and brush angle, in addition to the existing brush size slider.

- [X] Add the ability to control the brush direction. The stroke direction should be controlled four different ways: 
  - [X] using a slider value
  - [X] using the right mouse button to drag out a direction line
  - [X] using the direction of the cursor movement
  - [X] using directions that are perpendicular to the gradient of the image. 
  - You can use a radio box to allow the user to select which method to use.
  
- [X] Allow the user to change the opacity (alpha value) of the brush stroke. An alpha value slider should be added to the controls window.

Bonuses:
 
- [X] :notes: To give your paintings more variety, add some additional brush types to the program. These brush strokes should be substantially different from those you are required to implement. You will get one whistle for each new brush (within reason).

  - [X] :notes: The skeleton program allows the user to paint outside the boundary of the paint rectangle, then erases this region when the stroke is completed. Change this to clip brush strokes to the region as they're being painted.

    - [X] :notes: When using your program, you currently can't see what part of the original image you're painting. Extend the program so that when the cursor is in the painting window, a marker appears on the original image showing where you're painting.

      - [X] :notes: Sometimes it is useful to use the contents of the painting window as the original image. Add a control to swap the contents of the painting window and the contents of the original image window.

        - [X] :bell: Add controls that allow you to manipulate the color of the image. For example, you could implement independent scaling of the red, green, and blue channels.

          - [ ] :bell: Design a brush that selectively applies one or more filters such as blurring and sharpening.

            - [ ] :bell: Add an undo feature with at least one level of undo so that you can try a brush and decide to undo its effect on the canvas. This comes in very handy for experimenting with brush and filtering effects.

              - [ ] :bell: Add the ability to dissolve one image into another.

- [ ] :bell::notes: A different solution to the problem of not being able to see where you're painting is to show a dimmed version of the painting on the canvas. Add a slider that allows the user to fade in or fade out the original image beneath the user's brush strokes on the canvas. (Beware, this bell and whistle is more difficult than it looks).

- [ ] :bell::notes: Add a "mural" effect to your Impressionist by implementing the ability to load in different images while preserving what has been drawn on the canvas. Add a "New Mural Image" or "Change Mural Image" to the controls window that allows the user to change images. The user may then load an image, draw in what he / she prefers on the canvas, and then load a different image and continue drawing on the canvas; thus, a "mural" effect.

- [ ] :bell::notes: To make your painting more interesting, add "alpha-mapped" brush strokes. In other words, allow the user to load a bitmap representing a brush stroke. This bitmap would contain an alpha value at each position. Then when this brush is used to draw, a single color would be selected from the image, all pixels in the brush bitmap would be set to this RGB color (without changing the alpha value), and this partially transparent bitmap would be painted on the canvas. A new color would be used each time the brush is drawn.

- [ ] :bell::notes: It can be time-consuming to paint an image manually. Add a feature so that a whole painting can be created automatically. The user should only have to specify a brush type, size, and angle to use. Then the program should automatically paint brush strokes over the entire image, using a randomized brush order and varying the brush attributes slightly as it goes (to increase realism).

- [ ] :bell::notes: At times, you may want the brush strokes to follow the gradient of a different image than the base image. Add a button(s) that will cause the direction of brush strokes to be automatically determined from a user specified image.

  - [ ] :bell::notes: The "accuracy" of the painting can be also be improved by clipping long brush strokes to edges in the image. Allow the user to load a black-and-white image that represents the edges in the picture. Then add a checkbox so that the user can turn on edge-clipping, which will automatically clip brush strokes at edges in the image.

- [ ] :bell::bell: Construct a filter kernel design interface so that you can enter the weights of filters of arbitrary sizes. Provide an "apply" button that will cause the convolution to happen. Include a "normalize" checkbox that will automatically divide by the sum of the weights when the user wishes it.

  - [ ] :bell::bell: Use the image processing techniques described in class to automatically find the edges in the base image. Once you have found the edges, add a button to the user interface that will allow the user to select whether or not the brush strokes should be clipped to the edges in the picture.

- [ ] :bell::bell: Implement a multiresolution automatic painting technique. See Painterly Styles for Expressive Rendering.

  - [ ] :bell::bell: Design a brush that can be used to stretch and pull the image as if it were rubber. See Warp George Bush.

    - [ ] :bell::bell: Implement a curved brush that follows the image gradient. See Painterly Styles for Expressive Rendering.

      - [ ] :bell::bell::bell::bell: Given a source image, construct a new image that is really a mosaic of small (thumbnail) images. To do this, you need to partition the original into tiles and find new thumbnails that are reasonable matches to the tiles. Then draw the new image by substituting the thumbnails for the tiles. See, for example, Adam Finkelsteins Web Gothic. Credit will vary depending on the success of your method.

- [ ] :bell::bell::bell::bell: Extend the Impressionist program to work with video. The user should be able to load a series of images from a video and set up some initial parameters, and the program should automatically generate an impressionistic version of the video. The video should exhibit temporal coherency. 
 

- [ ] :bell::bell::bell::bell::bell::bell::bell::bell: Implement Bayesian matting.
