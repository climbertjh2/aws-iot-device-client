// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#include "../SharedCrtResourceManager.h"
#include "../config/Config.h"

#include <aws/iotidentity/IotIdentityClient.h>

namespace Aws
{
    namespace Iot
    {
        namespace DeviceClient
        {
            /**
             * \brief Provides IoT Fleet Provisioning related functionality within the Device Client
             */
            class FleetProvisioning
            {
              public:
                /**
                 * \brief Provisions device by creating and storing required resources
                 *
                 * @param fpConnection the MqttConnectionManager
                 * @param config configuration information passed in by the user via either the command line or
                 * configuration file
                 * @return returns true if device is provisioned successfully
                 */
                bool ProvisionDevice(std::shared_ptr<SharedCrtResourceManager> fpConnection, PlainConfig &config);
                std::string getName();

              private:
                /**
                 * \brief Used by the logger to specify that log messages are coming from the Fleet Provisioning feature
                 */
                static constexpr char TAG[] = "FleetProvisioning.cpp";
                /**
                 * \brief The default value in seconds for which Device client will wait for promise variables to be
                 * initialized. These promise variables will be initialized in respective callback methods
                 */
                static constexpr int DEFAULT_WAIT_TIME_SECONDS = 10;
                /**
                 * \brief an promise variable to check if publish request for CreateKeysAndCertificate was received
                 */
                std::promise<bool> keysPublishCompletedPromise;
                /**
                 * \brief an promise variable to check if subscription request to CreateKeysAndCertificate Accept topic
                 * was executed
                 */
                std::promise<bool> keysAcceptedCompletedPromise;
                /**
                 * \brief an promise variable to check if subscription to CreateKeysAndCertificate Reject topic was
                 * executed
                 */
                std::promise<bool> keysRejectedCompletedPromise;
                /**
                 * \brief an promise variable to check if publish request for CreateKeysAndCertificate was executed
                 */
                std::promise<bool> keysCreationCompletedPromise;
                /**
                 * \brief an promise variable to check if publish request for CreateKeysAndCertificate was executed.
                 * Client would know if the request was rejected using this promise variable
                 */
                std::promise<void> keysCreationFailedPromise;

                /**
                 * \brief an promise variable to check if publish request for RegisterThing was received
                 */
                std::promise<bool> registerPublishCompletedPromise;
                /**
                 * \brief an promise variable to check if subscription to RegisterThing Accept topic was
                 * executed
                 */
                std::promise<bool> registerAcceptedCompletedPromise;
                /**
                 * \brief an promise variable to check if subscription to RegisterThing Reject topic was
                 * executed
                 */
                std::promise<bool> registerRejectedCompletedPromise;
                /**
                 * \brief an promise variable to check if publish request for RegisterThing was executed
                 */
                std::promise<bool> registerThingCompletedPromise;
                /**
                 * \brief an promise variable to check if publish request for RegisterThing was executed.
                 * Client would know if the request was rejected using this promise variable
                 */
                std::promise<void> registerThingFailedPromise;

                /**
                 * \brief stores certificate Ownership Token
                 */
                Aws::Crt::String certificateOwnershipToken;
                /**
                 * \brief stores certificate file path of newly created certificate
                 */
                Aws::Crt::String certPath;
                /**
                 * \brief stores private key file path of newly created private key
                 */
                Aws::Crt::String keyPath;
                /**
                 * \brief stores thing name of newly provisioned device
                 */
                Aws::Crt::String thingName;
                /**
                 * \brief stores Fleet Provisioning template name
                 */
                Aws::Crt::String templateName;

                /**
                 * \brief creates a new certificate and private key using the AWS certificate authority
                 *
                 * @param identityClient used for subscribing and publishing request for creating resources
                 * @return returns true if resources are created successfully
                 */
                bool CreateCertificateAndKeys(Iotidentity::IotIdentityClient identityClient);
                /**
                 * \brief registers the device with AWS IoT and create cloud resources
                 *
                 * @param identityClient used for subscribing and publishing request for registering and  creating
                 * resources
                 * @return returns true if resources are registered and created successfully
                 */
                bool RegisterThing(Iotidentity::IotIdentityClient identityClient);
                /**
                 * \brief exports config of newly created resources to runtime config file
                 *
                 * @param file runtime config file path
                 * @param certPath newly created certificate file path
                 * @param keyPath newly created private key file path
                 * @param thingName thing name of newly provisioned device
                 * @return returns true if resources are registered and created successfully
                 */
                bool ExportRuntimeConfig(
                    const std::string &file,
                    const std::string &certPath,
                    const std::string &keyPath,
                    const std::string &thingName);
            };
        } // namespace DeviceClient
    }     // namespace Iot
} // namespace Aws
