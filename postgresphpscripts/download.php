<?php
$host        = "host = localhost";
$port        = "port = 5432";
$dbname      = "dbname = <dbname>";
$credentials = "user = <user> password=<psw>";

 $conn = pg_connect( "$host $port $dbname $credentials"  );

if (!$conn) {
  echo "An error occurred.\n";
  die("Error in connection: " . pg_last_error());
  exit;
}

$result = pg_query($conn, "SELECT * FROM Contacts");
if (!$result) {
  echo "An error occurred.\n";
  exit;
}
$emparray = array();

while ($row = pg_fetch_assoc($result)) {
    $emparray[] = $row;
}
 echo json_encode($emparray);

pg_free_result($result);
pg_close($conn);

?>