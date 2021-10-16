SELECT name
  FROM SONGS
 WHERE artist_id IN
       (SELECT id
          FROM artists AS a
         WHERE a.name = 'Post Malone');
