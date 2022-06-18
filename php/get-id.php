<?php
include 'koneksi.php';
$finger_id = (isset($_GET['id']));   
$query= mysqli_query($dbconnect, "INSERT INTO tb_finger(id) VALUES('$finger_id')");
if($query){
echo 'Berhasil disimpan';
}else{
echo 'Penyimpanan Gagal';
}
?>