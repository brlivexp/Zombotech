-- phpMyAdmin SQL Dump
-- version 3.2.4
-- http://www.phpmyadmin.net
--
-- Servidor: localhost
-- Tempo de Geração: Ago 06, 2015 as 08:46 
-- Versão do Servidor: 5.1.41
-- Versão do PHP: 5.3.1

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Banco de Dados: `dayz`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `equiped_items`
--

CREATE TABLE IF NOT EXISTS `equiped_items` (
  `playerid` int(11) NOT NULL,
  `slotid` int(11) NOT NULL,
  `itemid` int(11) NOT NULL,
  `modelid` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `durability` float NOT NULL DEFAULT '100',
  `time` int(24) NOT NULL DEFAULT '0',
  `expirable` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `equiped_items`
--

INSERT INTO `equiped_items` (`playerid`, `slotid`, `itemid`, `modelid`, `amount`, `durability`, `time`, `expirable`) VALUES
(1, 1, 2, 353, 441, 100, 0, 0),
(1, 0, 1, 355, 250, 100, 0, 0);

-- --------------------------------------------------------

--
-- Estrutura da tabela `items`
--

CREATE TABLE IF NOT EXISTS `items` (
  `id` int(11) NOT NULL,
  `model` int(11) NOT NULL,
  `amount` int(11) NOT NULL DEFAULT '1',
  `owner` int(11) NOT NULL,
  `coord_x` float NOT NULL,
  `coord_y` float NOT NULL,
  `coord_z` float NOT NULL,
  `world` int(11) NOT NULL DEFAULT '0',
  `interior` int(11) NOT NULL DEFAULT '0',
  `durability` float NOT NULL DEFAULT '100',
  `time` int(32) NOT NULL DEFAULT '0',
  `expirable` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `items`
--

INSERT INTO `items` (`id`, `model`, `amount`, `owner`, `coord_x`, `coord_y`, `coord_z`, `world`, `interior`, `durability`, `time`, `expirable`) VALUES
(1, 19578, 1, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(4, 359, 20, 1, 0, 0, 0, 0, 0, 100, 0, 0),
(3, 19574, 2, 1, 0, 0, 0, 0, 0, 100, 0, 0),
(2, 356, 33, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(6, 351, 25, 1, 0, 0, 0, 0, 0, 100, 0, 0),
(7, 2040, 25, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(8, 3016, 250, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(9, 3016, 125, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(10, 3016, 62, 1, -1, -1, -1, 0, 0, 100, 0, 0),
(11, 3016, 62, 1, -1, -1, -1, 0, 0, 100, 0, 0);

-- --------------------------------------------------------

--
-- Estrutura da tabela `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(24) NOT NULL,
  `password` varchar(32) NOT NULL,
  `mail` varchar(64) NOT NULL DEFAULT 'default@default.org',
  `adminlevel` int(11) NOT NULL DEFAULT '0',
  `kills` int(11) NOT NULL DEFAULT '0',
  `deaths` int(11) NOT NULL DEFAULT '0',
  `zombiekills` int(11) NOT NULL DEFAULT '0',
  `level` int(11) NOT NULL DEFAULT '0',
  `experience` int(11) NOT NULL DEFAULT '0',
  `health` float NOT NULL DEFAULT '100',
  `kevlar` float NOT NULL DEFAULT '0',
  `pos_x` float NOT NULL DEFAULT '0',
  `pos_y` float NOT NULL DEFAULT '0',
  `pos_z` float NOT NULL DEFAULT '0',
  `pos_a` float NOT NULL DEFAULT '0',
  `virtualworld` int(11) NOT NULL DEFAULT '0',
  `interior` int(11) NOT NULL DEFAULT '0',
  `lastlogin` int(11) NOT NULL DEFAULT '0',
  `vipcoins` int(11) NOT NULL DEFAULT '0',
  `bagtype` int(11) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Extraindo dados da tabela `users`
--

INSERT INTO `users` (`id`, `name`, `password`, `mail`, `adminlevel`, `kills`, `deaths`, `zombiekills`, `level`, `experience`, `health`, `kevlar`, `pos_x`, `pos_y`, `pos_z`, `pos_a`, `virtualworld`, `interior`, `lastlogin`, `vipcoins`, `bagtype`) VALUES
(1, 'ipsLeon', '4E9FBE888616FD89877E8DBF0E69999C', 'leo_style_lfm@hotmail.com', 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);

-- --------------------------------------------------------

--
-- Estrutura da tabela `users_skills`
--

CREATE TABLE IF NOT EXISTS `users_skills` (
  `userid` int(11) NOT NULL,
  `skillpoints` int(11) NOT NULL,
  `stealth` int(11) NOT NULL,
  `support` int(11) NOT NULL,
  `recon` int(11) NOT NULL,
  `assault` int(11) NOT NULL,
  `guerrilla` int(11) NOT NULL,
  `endurance` int(11) NOT NULL,
  `feeding` int(11) NOT NULL,
  `satiation` int(11) NOT NULL,
  `engineering` int(11) NOT NULL,
  `handicraft` int(11) NOT NULL,
  `absorption` int(11) NOT NULL,
  `reaction` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `users_skills`
--


-- --------------------------------------------------------

--
-- Estrutura da tabela `users_stats`
--

CREATE TABLE IF NOT EXISTS `users_stats` (
  `userid` int(11) NOT NULL,
  `hunger` float NOT NULL DEFAULT '0',
  `thirst` float NOT NULL DEFAULT '0',
  `energy` float NOT NULL DEFAULT '100',
  `radiation` float NOT NULL DEFAULT '0',
  `temperature` float NOT NULL DEFAULT '37'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `users_stats`
--


/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
