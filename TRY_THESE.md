
# Try These Ideas


(Jump)

Jump system that jump happen when player releases the
jump button. So the more holding the jump, the higher
the jump.  
But the maximum pre jump holding can't get very long,
so player learn it intuitively and not over using it.  

Like say is player push down the jump, player character
slows down and prepare for jump and when player releases
the button, jump starts.  
But player movement velocity also adds to the jump initial
velocity, so player should balance between movement velocity
and jump preparation.  

After jump starts player has no control over its airborne
movement.
But maybe adds ability for player to have some control
on fall speed. Like slow down to aim and shoot or
fall fast and punch down.

(Movement Snap)

On controller joystick make it so
movement direction snap to certain
degrees like 45 or 30.

(Modularization)

Modularize in such a way that things
that changes together, stays together.

(Unit Vectors By Angle)

```cpp
// Constant Values
vec2f32::unit_0   // 1, 0
vec2f32::unit_30
vec2f32::unit_45  // ~0.70, ~0.70
vec2f32::unit_60
vec2f32::unit_90  // 0, 1
vec2f32::unit_10
vec2f32::unit_5
vec2f32::unit_360
vec2f32::unit_pi6
vec2f32::unit_pi4
vec2f32::unit_pi3
vec2f32::unit_pi2
vec2f32::unit_2pi3
vec2f32::unit_3pi4
vec2f32::unit_5pi6
vec2f32::unit_5pi6
vec2f32::unit_pi
vec2f32::unit_7pi6
vec2f32::unit_5pi4
vec2f32::unit_...
vec2f32::unit_2pi
vec2f32::sin_45   // f32 value
vec2f32::cos_10
vec2f32::tan_90
```

(Angle Data Types)

```cpp
typedef degf32;
typedef degf64;
typedef radf32;
typedef radf64;
typedef degi32;
typedef radu32;
typedef radu32;

degf32::to_rad()
radf32::to_deg()

typedef turnf32;  // Turn or Revolution (aka rev)
typedef gonf32;   // Gradian


```

(Color System)

```cpp
typedef rgbf32;
typedef hsvf32
type

```
