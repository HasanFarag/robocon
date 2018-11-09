"""Library containing the rover's functions."""
import hardware as hw


class Rover:
    """Properties and methods of the rover."""

    # TODO Properties. What are the attributes and properties
    # of the rover?

    # Example - The rover has a processor board (raspberry pi)
    board = hw.Board  # This is how we create an object in python.
    boardType = board.type()

    # TODO Methods. What are the actions the rover has to be able
    # to perform?
	
	def moveForwards():
		#TODO
		pass
