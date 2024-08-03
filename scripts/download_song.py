import requests
import json
import sys
import os

def download_song(song_name,song_name_mp4, url):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    songs_dir = os.path.join(script_dir, "..", "songs")

    file_name = os.path.join(songs_dir, song_name_mp4)
    
    response = requests.get(url)
    if response.status_code == 200:
        with open(file_name, 'wb') as f:
            f.write(response.content)
    
    os.chdir(songs_dir)
    output_file_name = song_name + ".mp3"
    os.rename(file_name, output_file_name)
    

def fetch_data(song_name):
    url = "https://saavn.dev/api/search/songs"
    querystring = {"query" : song_name}
    response = requests.get(url, params=querystring)
    data = response.json()
    results_list = data['data']['results']

    name = results_list[0]['name']
    link_320kbps = results_list[0]['downloadUrl'][4]['url']

    song_name = song_name.replace(' ','')
    song_name_mp4 = song_name + ".mp4"
    download_song(song_name, song_name_mp4, link_320kbps)

def clear_old_songs():
    directory = os.path.join(os.getcwd(), "songs")
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
        except Exception as e:
            pass

if __name__ == '__main__':
    if len(sys.argv) > 1:
        song_name = sys.argv[1]
    else:
        pass
        # print("No song name provided!")
    clear_old_songs()
    fetch_data(song_name)
    