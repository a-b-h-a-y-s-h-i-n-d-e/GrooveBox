import requests
import json
import sys
import os

def download_song(song_name,song_name_mp4, url):
    # directory = os.path.join(os.getcwd(), "songs")
    directory = os.path.join(os.path.dirname(os.getcwd()), "songs")

    if not os.path.exists(directory):
        os.makedirs(directory)
    file_name = os.path.join(directory, song_name_mp4)

    response = requests.get(url)
    if response.status_code == 200:
        with open(file_name, 'wb') as f:
            f.write(response.content)

    os.chdir(directory)
    input_file_name = song_name_mp4
    output_file_name = song_name + ".mp3"
    os.rename(input_file_name, output_file_name)
    

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
    print(song_name_mp4)
    download_song(song_name, song_name_mp4, link_320kbps)

    
if __name__ == '__main__':
    if len(sys.argv) > 1:
        song_name = sys.argv[1]
    else:
        pass
        # print("No song name provided!")
    fetch_data(song_name)
    