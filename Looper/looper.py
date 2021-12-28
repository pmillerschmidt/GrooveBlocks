class Looper:
    """multidimensional array representing channels and steps"""
    ##looper profile with number of channels, tempo 
    def __init__(self, tempo,num_channels):
        self.tempo = tempo #none of these are really implemented yet
        self.num_channels = num_channels
        #initialize loops 
        self.loops = ['000'] * num_channels
        
    #basic set and get loop methods  
    def set_loop(self, channel, code):
        self.loops[channel - 1] = code

    def get_loop(self, channel):
        return self.loops[channel]


