#pragma once

/*
HandlerID is a enum that determines the Base IHandler classes ID.
ClientDistributer will make use of this information to provide mechanism of distributing peers, and finding them back.

*/

enum class HandlerID
{
	unspecified,
	lobby
};

