class MyClock24:
    def __init__(self, hours=0, minutes=0, seconds=0):
        if not (0 <= hours < 24) or not (0 <= minutes < 60) or not (0 <= seconds < 60):
            raise ValueError("Invalid time values")
        self._total_seconds = hours * 3600 + minutes * 60 + seconds

    @property
    def hours(self):
        return self._total_seconds // 3600

    @property
    def minutes(self):
        return (self._total_seconds % 3600) // 60

    @property
    def seconds(self):
        return self._total_seconds % 60

    def tick(self):
        self._total_seconds = (self._total_seconds + 1) % (24 * 3600)

    def __str__(self):
        return f"{self.hours:02d}:{self.minutes:02d}:{self.seconds:02d}"

    def __repr__(self):
        return f"{{'hours': {self.hours}, 'minutes': {self.minutes}, 'seconds': {self.seconds}}}"

    def __eq__(self, other):
        return self._total_seconds == other._total_seconds if isinstance(other, MyClock24) else False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __ge__(self, other):
        return self._total_seconds >= other._total_seconds if isinstance(other, MyClock24) else False

    def __gt__(self, other):
        return self._total_seconds > other._total_seconds if isinstance(other, MyClock24) else False

    def __le__(self, other):
        return self._total_seconds <= other._total_seconds if isinstance(other, MyClock24) else False

    def __lt__(self, other):
        return self._total_seconds < other._total_seconds if isinstance(other, MyClock24) else False

    def __add__(self, other):
        if isinstance(other, MyClock24):
            total_seconds = (self._total_seconds + other._total_seconds) % (24 * 3600)
            return MyClock24(seconds=total_seconds)
        elif isinstance(other, int):
            total_seconds = (self._total_seconds + other) % (24 * 3600)
            return MyClock24(seconds=total_seconds)
        else:
            raise TypeError("Unsupported operand type")

    def __radd__(self, other):
        return self.__add__(other)

    def __sub__(self, other):
        if isinstance(other, MyClock24):
            total_seconds = self._total_seconds - other._total_seconds
        elif isinstance(other, int):
            total_seconds = self._total_seconds - other
        else:
            raise TypeError("Unsupported operand type")
    
    # Handle rollovers
        if total_seconds < 0:
            total_seconds += (24 * 3600)

    # Calculate hours, minutes, and seconds
        hours = total_seconds // 3600
        minutes = (total_seconds % 3600) // 60
        seconds = total_seconds % 60

        return MyClock24(hours=hours, minutes=minutes, seconds=seconds)


    def __rsub__(self, other):
        return self.__sub__(other)
