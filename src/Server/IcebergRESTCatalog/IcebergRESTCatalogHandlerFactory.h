#pragma once

#include <Server/HTTP/HTTPRequestHandlerFactory.h>
#include <Server/IcebergRESTCatalog/IcebergRESTCatalogService.h>
#include <Common/logger_useful.h>

namespace Poco::Util
{
class AbstractConfiguration;
}

namespace DB
{

class IServer;

class IcebergRESTCatalogHandlerFactory : public HTTPRequestHandlerFactory
{
public:
    IcebergRESTCatalogHandlerFactory(IServer & server_, IcebergRESTCatalogServicePtr service_);

    std::unique_ptr<HTTPRequestHandler> createRequestHandler(const HTTPServerRequest & request) override;

private:
    const std::string name = "IcebergRESTCatalogHandler-factory";
    LoggerPtr log;
    IServer & server;
    IcebergRESTCatalogServicePtr service;
};

/// Builds the single warehouse from the `iceberg_rest_catalog` section of the server config.
/// The config is temporary scaffolding. Warehouses will be stored in Keeper and managed with SQL later.
HTTPRequestHandlerFactoryPtr createIcebergRESTCatalogHandlerFactory(IServer & server, const Poco::Util::AbstractConfiguration & config);

}
