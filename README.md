
**Describe the effect each of the P, I, D components had in your implementation.**

The *Proportional* term is as as its name implies, proportional to the error, and thus produces a contorl signal that matches the error's. May cause overshoot.

The *Intergral* term is multiplied by the summation of the error over time and it is the most contributing factor in reaching steady state error.

The *Derivative* term predicts the error as it compensates againist its rate of change thus giveing a *damping* effect and decreases the overshoot.

**Describe how the final hyperparameters were chosen.**

My hyper parameters were chosen using technique explained in the lessons, which is the *Twiddle* optimization algorithm.

In the end (after a little over 100 runs), The optimal controler reached was a PD controller with the following parameters:
`
P = 0.196632, 
I = 0.0, 
D =  1.44655 
`

The intergral term was not critical for the control of the car to stay on track.
