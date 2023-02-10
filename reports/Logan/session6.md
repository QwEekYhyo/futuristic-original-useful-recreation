# Session 6 report

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;So during this session I coded an animation when you win a game. It consists of making the 4 winning coins blink a few times. Here is
how I managed to do this :

- I added a private attribute to the `board` class : `array<array<int, 2>, 4> winning_seg;`, this is an array of size 4 containing arrays of size 2, this corresponds to
the 4 coordinates of the winning coins. The value of this attribute is not changed until the game is won by a player.
- Then I added a `void win_anim()` public method to the class. It is implemetented in this way :
  
  ```
  player winner = at(winning_seg.at(0));
  // Because it is the winning segment, all 4 coordinates point to the same player so I chose to get the first one and stored
  // it into a variable of type `player` which is an enumeration fairly simple (it can either be one, two or none)
  
  for (int i = 0; i < 4; i++) {
  // then there's the first for loop that is done 4 times because I wanted the LEDs to blink 4 times
  
    for (int j = 0; j < 4; j++) {
    // the first nested for loop changes all of the players at the winning coordinates to 'none' so that the LEDs are shown
    // as turned off
      auto coord = winning_seg.at(j);
      at(coord) = player::none;
    }
    
    // after this we update the board
    // this method sets all of the LEDs to the corresponding color of the player in the game matrix
    // and there's a delay so that the animation isn't too fast
    update();
    delay(500);
    
    for (int j = 0; j < 4; j++) {
    // this second nested for loop sets back the winning coordinates to the right player stored before
      auto coord = winning_seg.at(j);
      at(coord) = winner;
    }
    // and again we update the LEDs
    update();
    delay(500);
  }
  ```
 - Then I had to use the `winning_seg` private attribute mentionned above, this was done in the `player get_winner()` method.
  This method returns a player, either the winning player or `player::none` if no one has won yet. The ending of each directionnal checking used to be : `if (winner != player::none) {return winner;}`
  which basically means that if, out of all of the segments of size 4 checked using the `player board::get_winner_from_arr(const array<array<int, 2>, 4> &coords) const` method, a real player is found,
  not none, we will return it and if nothing is returned we continue checking. I changed the lines to this : <br />
  `if (winner != player::none) {winning_seg.fill(segment); return winner;}` so that we
  don't only return the winning player but also store the 4 winning coordinates. The `fill()` method is defined in the `array` class and basically replaces all values
  of an array with the ones of another array.
  
  The corresponding commit can be found ![here](https://github.com/QwEekYhyo/futuristic-original-useful-recreation/commit/d66c8f9f9c0f1503382514f250cb59cd7680f6d3).
