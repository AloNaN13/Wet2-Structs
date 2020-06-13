





#ifndef WET1_STRUCTS_ARTIST_H
#define WET1_STRUCTS_ARTIST_H

#include "AvlTree.h"
#include "List.h"


class Artist{
private:
    int artist_id;
    int total_num_of_songs;
    StreamListNode** full_songs_list;
    AvlTree<AvlTree<int,int>,int> num_of_streams_tree;
public:
    Artist(int id, int num_of_songs);
    ~Artist();
    Artist(const Artist& a);
    Artist& operator=(const Artist& a) = default;

    //getters-
    StreamListNode* GetSongNumOfStreamsNode(int song_id);
    int GetTotalNumOfSongs() {return this->total_num_of_songs;};
    AvlTree<AvlTree<int,int>,int>& GetNumOfStreamsTree() {return this->num_of_streams_tree;};
    int GetArtistID() {return this->artist_id;};
    /*AvlTree<int,int>* getSongsWithNumOfStreams(const Key& key){
        return num_of_streams_tree.getElementptr(key);
    }
     */

    //setters
    void SetStreamsNumForSong(int song_id, StreamListNode* wanted_node);

};


#endif //WET1_STRUCTS_ARTIST_H
