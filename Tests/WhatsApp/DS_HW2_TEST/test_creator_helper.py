import functools
import random

INVALID="INVALID_INPUT"
FAILURE="FAILURE"
SUCCESS="SUCCESS"


def compare_songs(song1,song2):
    if (song2["count"]-song1["count"])!=0:
        return song2["count"]-song1["count"]
    elif (song1["artist"]-song2["artist"])!=0:
        return song1["artist"]-song2["artist"]
    else:
        return song1["song"]-song2["song"]


def create_in_out_files(test_name):
    in_file = open("./tests/in/in"+test_name+".txt","w")
    out_file = open("./tests/out/out"+test_name+".txt","w")
    return in_file,out_file


def get_song_key(artist_id,song_id):
    return f"{artist_id}_{song_id}"


def get_status_str(pre,result):
    return f"{pre}: {result}"


a =-3
b = 70


# +
class MMTestCreator:

    def __init__(self,test_name):
        self.init_called = False
        self.songs = {}
        self.artists = {}
        self.in_file,self.out_file = create_in_out_files(test_name)
        self.random_func = [self.add_song_rand,
                 self.add_artist_rand,
                 self.add_to_song_count_rand,
                 self.get_rec_song_in_place_rand,
                 self.get_artist_best_song_rand,
                 self.remove_song_rand,
                 self.remove_artist_rand,
                ]
        self.funcs =self.random_func+[self.add_init,self.quit]
        
    def finish(self):
        self.in_file.close()
        self.out_file.close()

        
    def make_random_action(self):
        action = random.randint(0,len(self.funcs)-1)
        self.funcs[action]()
    
    def make_random_action_no_quit_no_init(self):
        action = random.randint(0,len(self.random_func)-1)
        self.random_func[action]()
    
    def add_line(self,command,expected):
        self.in_file.write(command+"\n")
        self.out_file.write(expected+"\n")    
        print(expected)
        
    def add_init(self):
        if not self.init_called:
            self.add_line("Init","init done.")
            self.init_called=True
        else:
            self.add_line("Init","init was already called.")
            
    def add_song(self,id_artist,id_song):
        pre = "AddSong"
        command = f"{pre} {id_artist} {id_song}"
        if id_artist<=0 or id_song<=0 or not self.init_called:
            self.add_line(command,f"{pre}: {INVALID}")
        elif id_artist not in self.artists or get_song_key(id_artist,id_song) in self.songs:
            self.add_line(command,f"{pre}: {FAILURE}")
        else:
            self.add_line(command,f"{pre}: {SUCCESS}")
            self.songs[get_song_key(id_artist,id_song)] = {"artist":id_artist,"song":id_song,"count":0}
            
    def add_song_rand(self):
        self.add_song(random.randint(a,b),random.randint(a,b))
            
    def add_artist(self,id_artist):
        pre = "AddArtist"
        command = f"{pre} {id_artist}"
        
        if id_artist<=0 or not self.init_called:
            self.add_line(command,f"{pre}: {INVALID}")
        elif id_artist in self.artists:
            self.add_line(command,f"{pre}: {FAILURE}")
        else:
            self.add_line(command,f"{pre}: {SUCCESS}")
            self.artists[id_artist] = True
            
    def add_artist_rand(self):
        self.add_artist(random.randint(a,b))
    
    def get_songs_sorted(self):
        songs = list(self.songs.values())
        sorted_songs = sorted(songs,key=functools.cmp_to_key(compare_songs))
        return sorted_songs
    
    def get_artist_songs_sorted(self,id_artist):
        sorted_songs = self.get_songs_sorted()
        return list(filter(lambda song:song["artist"]==id_artist,sorted_songs))
    
    def add_to_song_count(self,artist_id,song_id,count):
        pre = "AddToSongCount"
        command = f"{pre} {artist_id} {song_id} {count}"
        if artist_id<=0 or song_id<=0 or count<=0 or not self.init_called:
            self.add_line(command,get_status_str(pre,INVALID))
        elif get_song_key(artist_id,song_id) not in self.songs:
            self.add_line(command,get_status_str(pre,FAILURE))
        else:
            self.songs[get_song_key(artist_id,song_id)]["count"] += count
            self.add_line(command,get_status_str(pre,SUCCESS))

    def add_to_song_count_rand(self):
        self.add_to_song_count(random.randint(a,b),random.randint(a,b),random.randint(a,b))

    def get_rec_song_in_place(self,rank):
        pre = "GetRecommendedSongInPlace"
        command = f"{pre} {rank}"
        if(rank<=0 or not self.init_called):
            self.add_line(command,get_status_str(pre,INVALID))
        elif len(list(self.songs.values()))<rank:
            self.add_line(command,get_status_str(pre,FAILURE))
        else:
            sorted_songs = self.get_songs_sorted()
            song = sorted_songs[rank-1]
            artist_id = song["artist"]
            song_id = song["song"]
            self.add_line(command,get_status_str(pre,f"Artist {artist_id} Song {song_id}"))
            
    def get_rec_song_in_place_rand(self):
        self.get_rec_song_in_place(random.randint(a,b))

    def get_artist_best_song(self,id_artist):
        pre = "GetArtistBestSong"
        command = f"{pre} {id_artist}"
        if id_artist<=0 or not self.init_called:
            self.add_line(command,get_status_str(pre,INVALID))
        elif len(self.get_artist_songs_sorted(id_artist))==0:
            self.add_line(command,get_status_str(pre,FAILURE))
        else:
            artist_best_song = self.get_artist_songs_sorted(id_artist)[0]
            self.add_line(command,get_status_str(pre,artist_best_song["song"]))
            
    def get_artist_best_song_rand(self):
        self.get_artist_best_song(random.randint(a,b))
        
    def remove_song(self,id_artist,id_song):
        pre = "RemoveSong"
        command = f"{pre} {id_artist} {id_song}"
        if id_artist<=0 or id_song<=0 or not self.init_called:
            self.add_line(command,get_status_str(pre,INVALID))
        elif get_song_key(id_artist,id_song) not in self.songs:
            self.add_line(command,get_status_str(pre,FAILURE))
        else:
            del self.songs[get_song_key(id_artist,id_song)]
            self.add_line(command,get_status_str(pre,SUCCESS))
                          
    def remove_song_rand(self):
        self.remove_song(random.randint(a,b),random.randint(a,b))
        
    def remove_artist(self,artist_id):
        pre = "RemoveArtist"
        command = f"{pre} {artist_id}"
        if artist_id<=0 or not self.init_called:
            self.add_line(command,get_status_str(pre,INVALID))

        elif artist_id not in self.artists or len(self.get_artist_songs_sorted(artist_id))>0:
            self.add_line(command,get_status_str(pre,FAILURE))
        else:
            del self.artists[artist_id]
            self.add_line(command,get_status_str(pre,SUCCESS))
            
    def remove_artist_rand(self):
        self.remove_artist(random.randint(a,b))
            
    def quit(self):
        self.init_called= False
        command = "Quit"
        self.add_line(command,"quit done.")
        self.songs = {}
        self.artists = {}


# -

def make_random_test(length,test_name):
    with_init = int(length/10)
    no_init = int(length*8/10)
    test_creator = MMTestCreator(test_name)
    for i in range(with_init):
        test_creator.make_random_action()
        
    test_creator.add_init()
    
    for i in range(no_init):
        test_creator.make_random_action_no_quit_no_init()
    
    for i in range(with_init):
        test_creator.make_random_action()
    test_creator.quit()
    test_creator.finish()
        


make_random_test(100000,"_test_100000")


