<?php
include "koneksi.php";
$query = mysqli_query($dbconnect,"SELECT * FROM tb_finger ORDER BY id ASC");
?>
<form action="" method="post">
    <table border="1" cellpadding="0" cellspacing="0">
        <tr>
            <th>No</th>
            <th>Username</th>
        </tr>
        <?php if(mysqli_num_rows($query)>0){ ?>
        <?php
            $no = 1;
            while($data = mysqli_fetch_array($query)){
        ?>
        <tr>
            <td><?php echo $no ?></td>
            <td><?php echo $data["username"];?></td>
            <td><?php echo $data["password"];?></td>
        </tr>
        <?php $no++; } ?>
        <?php } ?>
    </table>
</form>