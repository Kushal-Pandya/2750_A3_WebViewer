<html>
<body>

<?php 

$cmd = './a3 view.wpml';
exec($cmd, $output, $status);

if ($status)
	echo 'exec failed';
else {
	foreach ($output as $line) {
		echo $line;
	}
}



session_start();
$author = $_SESSION['author'];

echo 'Viewing Stream: ' . $_POST['stream'] . ' <br><br>';

$cmd2 = './view.py ' . $author . ' *' . $_POST['stream'];
$output2 = shell_exec($cmd2);

echo "<pre>" . $output2 . "</pre>";


?>

</body>
</html> 