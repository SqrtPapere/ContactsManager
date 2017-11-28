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

$id = $_POST["id"];


$sql = "DELETE FROM Contacts WHERE Contacts.ID = '$id'";

$result = pg_query($conn, $sql);
if (!$result) {
    die("Error in SQL query: " . pg_last_error());
}
echo "Data successfully inserted!";

pg_free_result($result);
pg_close($conn);
?>
