from PythonFramework.Strategy.Strategy import Strategy
from PythonFramework.Command import Command
from PythonFramework.Util.Pose import Pose
#from jstick import Joystick


class RemoteStrategy(Strategy):
    def __init__(self, field, referee, team, opponent_team, is_team_yellow=False):
        Strategy.__init__(self, field, referee, team, opponent_team)

        # Create InfoManager
        self.team.is_team_yellow = is_team_yellow

    def on_start(self):
        self._send_command(Command.MoveToAndRotate(self.team.players[0], self.team, Pose()))

    def on_halt(self):
        self.on_start()

    def on_stop(self):
        self.on_start()
