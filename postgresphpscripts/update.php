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
$name = $_POST["name"];
$surname = $_POST["surname"];
$phone = $_POST["phone"];
$note = $_POST["note"];
$tag = $_POST["tag"];


if (empty($phone)) {
	die("Empty phone: ");
  	exit;
}
$email = $_POST["email"];

$sql = "UPDATE Contacts SET NAME='$name', SURNAME='$surname', PHONE='$phone', EMAIL='$email', NOTE='$note', TAG='$tag' WHERE ID='$id'";

$result = pg_query($conn, $sql);
if (!$result) {
    die("Error in SQL query: " . pg_last_error());
}
echo "Data successfully inserted!";

pg_free_result($result);
pg_close($conn);
?>
