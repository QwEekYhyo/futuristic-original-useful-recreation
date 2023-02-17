# Session 7 report

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Here is what I've done since last time :
- I added an `initializer_list` class, you can see the class definition in this
  ![file](https://github.com/QwEekYhyo/futuristic-original-useful-recreation/blob/inoed/game/initializer_list.hpp). The role of this class is to simplify some things like iteration and
initialization for my `array` class. The code of the `initializer_list` class
is from the C++ standard library, I just tweaked it a little bit to work on
arduino. I also had to modifiy my `array` class. Thanks to this, I refactored
the code a bit, and to simplify it even more I used aliases like : 
```
template <typename T>
using pair = array<T, 2>;
```
because my `array` class is very general but I use a lot of a specific sizes or
types. For exemple the alias defined in the code above is an array of type `T`
and size 2, very handy.
- A while back I added, 2 class attributes of type `Adafruit_NeoPixel` to my
  `board` class so I can display the game on the LED matrix. But I encountered
a problem when implementing the AI (that I will describe later). In the AI
algorithm we do a lot of copies of the `board` object, this implies that we
also do a lot of copies of the `Adafruit_NeoPixel` objects and this messed with
the display. So the attributes are now pointers to `Adafruit_NeoPixel`. This
means that I had to change the code a little bit but this also means that we
are now copying pointers and this fixes the display.
- I also made that the cursor to choose columns is displayed on the top LED
  band.
- Another small but very handful change : I made the methods `void loop()` and
  `void setup()` used for arduino friend of the `board` class. Thanks to this
I can access private attributes of the class in these methods.
- And now AI explanation. Firslty, I added a `pair<player> real_players`
  attribute to the `board` class, this is initialized in the constructor of
the class and used to choose which player is a real player and which player in
an AI. There is a `int random_playable_column() const` method, but it is only
used when running the code on a computer because from what I know, there is no
random on arduino. This method is used when the algorithm finds multiple
columns to have the same score (more on that later), in this case we choose
randomly between them except on arduino where we just choose the first one.
Then there is this method : 
```
template <int N>
int count_in_arr(const array<coords, N>& coordinates, const player& target_player) const
```
A pretty straightforward one, it counts how many of a player there is in
a segment of size N in the game. Then we need the `int evaluate_arr(const array<coords, 4>& coordinates, const player& current_player) const` method.
Its role is to determine a score from a segment of 4. It uses the
`count_in_arr` method and if there is a lot of the player we want in the
segment it returns a good score and vice versa. The `int evaluate_position(const player& current_player) const` method
uses the `evaluate_arr` method and goes through all of the game matrix,
vertically, horizontally and diagonally to determine a global score for the
targeted player in the current state of the game. And then, where the real
thing begins, the `friend pair<int> minimax(const board& b, int depth, int alpha, int beta, bool maximizing_player)` method.
This algorithm gets his name from the fact that it tries to minimize the score of the opponent and
maximize the score of the targeted player. It is used in a lot of other games, it works recursively and the general idea behind this algorithm
is to go through every single possible move by copying the current state of the
game and play in every copy, then play as the opponent the same way over and
over again (you can choose a recursion depth and in my case it is not very high
because Arduino does not have a lot of computing power) and once you hit the
furthest point you wanted to go, you go back by choosing the highest score on
your moves and the lowest score for the opponent. 

You can see all of the changes ![here](https://github.com/QwEekYhyo/futuristic-original-useful-recreation/compare/d66c8f9...8f2298d).
