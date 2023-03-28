handlers.ListCatalogCharacters = function (args, context) {

    var chars = [];
    
    // get all items from specifed catalog
    var items = server.GetCatalogItems({
        CatalogVersion: args.CatalogVersion
    });
    
    // get owned characters
    var myChars = server.GetAllUsersCharacters({
        PlayFabId: currentPlayerId
    }).Characters;
    
    // list characters
    for (var i in items.Catalog) {
        var item = items.Catalog[i];
        if (item.CanBecomeCharacter) {
            var char = {
                ItemId : item.ItemId,
                DisplayName: item.DisplayName,
                VirtualPrice: item.VirtualCurrencyPrices.GD,
                ItemImageUrl: item.ItemImageUrl
            };
            for (var j in myChars) {
                if (myChars[j].CharacterType == item.ItemId) {
                    char.Owned = true;
                    break;
                }
            }
            chars.push(char);
        }
    }
    
    return { Characters: chars };
};