<?php
/**
 *  Операции с базой данных (формирование запросов)
 */
//--------------------------------------------------------------------
require_once('dmozdatabasedefine.php');
//--------------------------------------------------------------------
/**
 * Установка связи с базой данных
 * 
 */
function connectDataBase()
{
	global $Link;
	if (!($Link = mysql_connect(DBADDRESS, DBUSER, DBPASSWORD)))
	{
		throw new Exception(CONNECT_ERROR . "\n", 0);
	}
}
//--------------------------------------------------------------------
/**
 * Разрыв связи с базой данных
 * 
 */
function disconnectDataBase()
{
	global $Link;
	mysql_close($Link);
}
//--------------------------------------------------------------------
/**
 * Выбор базы данных
 * 
 */
function selectDataBase()
{
	global $Link;
	if (!(mysql_select_db (DBNAME, $Link)))
	{
		throw new Exception(sprintf(SELECT_ERROR . "\n", DBNAME), 0);
	}
}
//--------------------------------------------------------------------
/**
 * Вставка данных в базу (INSERT)
 * 
 */
function insertDataBase($value)
{
	global $Link;
	if (($value = trim((string)$value)) != "")
	{
		$query = "INSERT INTO " . $value;
		if (!mysql_query($query, $Link))
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
}
//--------------------------------------------------------------------
/**
* Изменение структуры таблицы (ALTER)
*
*/
function alterTable($value)
{
	global $Link;
	if (($value = trim((string)$value)) != "")
	{
		$query = "ALTER TABLE " . $value;
		if (!mysql_query($query, $Link))
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
}
//--------------------------------------------------------------------
/**
 * Изменение данных в базе (UPDATE)
 * 
 */
function updateTable($value)
{
	global $Link;
	if (($value = trim((string)$value)) != "")
	{
		$query = "UPDATE " . $value;
		if (!mysql_query($query, $Link))
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
}
//--------------------------------------------------------------------
/**
 * Удаление данных из таблицы (DELETE)
 *
 */
function deleteTable($value)
{
	global $Link;
	if (($value = trim((string)$value)) != "")
	{
		$query = "DELETE FROM " . $value;
		if (!mysql_query($query, $Link))
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
}
//--------------------------------------------------------------------
/**
 * Полная очистка таблицы (DELETE)
 *
 */
function truncateTable($value)
{
	global $Link;
	if (($value = trim((string)$value)) != "")
	{
		$query = "TRUNCATE TABLE " . $value;
		if (!mysql_query($query, $Link))
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
}
//--------------------------------------------------------------------
/**
 * Выборка данных из таблицы (SELECT)
 *
 */
function selectData($value)
{
	global $Link;
	$result = "";
	if (($value = trim((string)$value)) != "")
	{
		$query = "SELECT " . $value;
		if (($result = mysql_query($query, $Link)) === false)
		{
			throw new Exception(mysql_error($Link), 0);
		}
	}
	return $result;
}
//--------------------------------------------------------------------
?>
